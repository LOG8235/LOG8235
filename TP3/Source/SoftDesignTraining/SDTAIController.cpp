// Fill out your copyright notice in the Description page of Project Settings.

#include "SDTAIController.h"
#include "SDTChaseGroup.h"
#include "SoftDesignTraining.h"
#include "SDTCollectible.h"
#include "SDTFleeLocation.h"
#include "SDTPathFollowingComponent.h"
#include "Kismet/KismetMathLibrary.h"
//#include "UnrealMathUtility.h"
#include "SDTUtils.h"
#include "EngineUtils.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Engine/World.h"
#include "Camera/PlayerCameraManager.h"
#include "GameFramework/PlayerController.h"

namespace
{
    constexpr float VisibleTickInterval = 0.08f;
    constexpr float HiddenTickInterval = 0.25f;

    constexpr float CollectMoveRequestCooldown = 0.35f;
    constexpr float ChaseMoveRequestCooldown = 0.20f;
    constexpr float FleeMoveRequestCooldown = 0.40f;

    constexpr float PerceptionUpdateVisible = 0.10f;
    constexpr float PerceptionUpdateHidden = 0.30f;

    constexpr float LoSUpdateVisible = 0.15f;
    constexpr float LoSUpdateHidden = 0.35f;

    constexpr float TargetRefreshDistSq = 100.f * 100.f;
}

ASDTAIController::ASDTAIController(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer.SetDefaultSubobjectClass<USDTPathFollowingComponent>(TEXT("PathFollowingComponent")))
{
    m_PlayerInteractionBehavior = PlayerInteractionBehavior_Collect;
    PrimaryActorTick.bCanEverTick = true; 
    PrimaryActorTick.bStartWithTickEnabled = true; 
    PrimaryActorTick.TickInterval = HiddenTickInterval + FMath::FRandRange(0.0f, 0.02f);
}

void ASDTAIController::GoToBestTarget(float deltaTime)
{
    switch (m_PlayerInteractionBehavior)
    {
    case PlayerInteractionBehavior_Collect:

        MoveToRandomCollectible();

        break;

    case PlayerInteractionBehavior_Chase:

        MoveToEncirclementPosition();

        break;

    case PlayerInteractionBehavior_Flee:

        MoveToBestFleeLocation();

        break;
    }
}

void ASDTAIController::MoveToRandomCollectible()
{
    static TArray<TWeakObjectPtr<ASDTCollectible>> CachedCollectibles;
    static float LastCollectibleCacheTime = 0.f;
    const float CollectibleCacheInterval = 2.0f;

    UWorld* World = GetWorld();
    if (!World)
        return;

    const float Now = World->GetTimeSeconds();

    if (CachedCollectibles.Num() == 0 || Now - LastCollectibleCacheTime > CollectibleCacheInterval)
    {
        CachedCollectibles.Reset();

        TArray<AActor*> FoundActors;
        UGameplayStatics::GetAllActorsOfClass(World, ASDTCollectible::StaticClass(), FoundActors);

        for (AActor* Actor : FoundActors)
        {
            ASDTCollectible* Collectible = Cast<ASDTCollectible>(Actor);
            if (IsValid(Collectible))
            {
                CachedCollectibles.Add(Collectible);
            }
        }

        LastCollectibleCacheTime = Now;
    }

    int32 NumAttempts = CachedCollectibles.Num();

    while (NumAttempts > 0 && CachedCollectibles.Num() > 0)
    {
        const int32 Index = FMath::RandRange(0, CachedCollectibles.Num() - 1);
        ASDTCollectible* CollectibleActor = CachedCollectibles[Index].Get();

        if (!IsValid(CollectibleActor))
        {
            CachedCollectibles.RemoveAt(Index);
            continue;
        }

        if (!CollectibleActor->IsOnCooldown())
        {
            RequestMoveIfNeeded(CollectibleActor->GetActorLocation(), 0.5f, CollectMoveRequestCooldown, true);
            return;
        }

        --NumAttempts;
    }
}

void ASDTAIController::MoveToPlayer()
{
    ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    if (!PlayerCharacter)
        return;

    RequestMoveIfNeeded(PlayerCharacter->GetActorLocation(), 0.5f, ChaseMoveRequestCooldown, true);
}

void ASDTAIController::MoveToEncirclementPosition()
{
    ASDTChaseGroup* Group = GetOrCreateChaseGroup();

    if (!Group || !Group->HasValidLKP() || Group->GetMemberCount() <= 1)
    {
        MoveToPlayer();
        return;
    }

    const FVector TargetPos = Group->GetEncirclementPositionFor(this);
    RequestMoveIfNeeded(TargetPos, 0.5f, ChaseMoveRequestCooldown, true);
}


void ASDTAIController::PlayerInteractionLoSUpdate()
{
    UWorld* World = GetWorld();
    if (!World)
        return;

    const float Now = World->GetTimeSeconds();
    const bool bVisibleRelevant = IsRelevantToPlayerView();
    const float LoSInterval = bVisibleRelevant ? LoSUpdateVisible : LoSUpdateHidden;

    if (Now < m_NextLoSUpdateTime)
        return;

    m_NextLoSUpdateTime = Now + LoSInterval;

    ACharacter * playerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    if (!playerCharacter)
        return;

    TArray<TEnumAsByte<EObjectTypeQuery>> TraceObjectTypes;
    TraceObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic));
    TraceObjectTypes.Add(UEngineTypes::ConvertToObjectType(COLLISION_PLAYER));

    FHitResult losHit;
    GetWorld()->LineTraceSingleByObjectType(losHit, GetPawn()->GetActorLocation(), playerCharacter->GetActorLocation(), TraceObjectTypes);

    bool hasLosOnPlayer = losHit.GetComponent() &&
                  losHit.GetComponent()->GetCollisionObjectType() == COLLISION_PLAYER;
    if (hasLosOnPlayer)
    {
		// Update de la LKP partagée avec la position actuelle du joueur
        ASDTChaseGroup* Group = GetOrCreateChaseGroup();
        if (Group)
            Group->UpdateLKP(playerCharacter->GetActorLocation());
        if (GetWorld()->GetTimerManager().IsTimerActive(m_PlayerInteractionNoLosTimer))
        {
            GetWorld()->GetTimerManager().ClearTimer(m_PlayerInteractionNoLosTimer);
            m_PlayerInteractionNoLosTimer.Invalidate();
        }
    }
    else
    {
        if (!GetWorld()->GetTimerManager().IsTimerActive(m_PlayerInteractionNoLosTimer))
        {
            GetWorld()->GetTimerManager().SetTimer(m_PlayerInteractionNoLosTimer, this, &ASDTAIController::OnPlayerInteractionNoLosDone, 3.f, false);
        }
    }
    
}

void ASDTAIController::OnPlayerInteractionNoLosDone()
{
    GetWorld()->GetTimerManager().ClearTimer(m_PlayerInteractionNoLosTimer);

    if (!AtJumpSegment)
    {
        AIStateInterrupted();
        m_PlayerInteractionBehavior = PlayerInteractionBehavior_Collect;
		UpdateGroupMembership(); 
    }
}

void ASDTAIController::MoveToBestFleeLocation()
{
    static TArray<TWeakObjectPtr<ASDTFleeLocation>> CachedFleeLocations;
    static float LastFleeCacheTime = 0.f;
    constexpr float FleeCacheInterval = 5.0f;

    UWorld* World = GetWorld();
    APawn* SelfPawn = GetPawn();
    ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(World, 0);

    if (!World || !SelfPawn || !PlayerCharacter)
        return;

    const float Now = World->GetTimeSeconds();

    if (CachedFleeLocations.Num() == 0 || Now - LastFleeCacheTime > FleeCacheInterval)
    {
        CachedFleeLocations.Reset();

        for (TActorIterator<ASDTFleeLocation> It(World, ASDTFleeLocation::StaticClass()); It; ++It)
        {
            if (IsValid(*It))
            {
                CachedFleeLocations.Add(*It);
            }
        }

        LastFleeCacheTime = Now;
    }

    float BestScore = -FLT_MAX;
    FVector BestTarget = FVector::ZeroVector;

    FVector SelfToPlayer = PlayerCharacter->GetActorLocation() - SelfPawn->GetActorLocation();
    SelfToPlayer.Normalize();

    for (int32 i = CachedFleeLocations.Num() - 1; i >= 0; --i)
    {
        ASDTFleeLocation* FleeLocation = CachedFleeLocations[i].Get();
        if (!IsValid(FleeLocation))
        {
            CachedFleeLocations.RemoveAtSwap(i);
            continue;
        }

        FVector SelfToFlee = FleeLocation->GetActorLocation() - SelfPawn->GetActorLocation();
        const float DistToFlee = SelfToFlee.Size();
        SelfToFlee.Normalize();

        const float Dot = FVector::DotProduct(SelfToPlayer, SelfToFlee);
        // Dot near -1 means opposite direction from player, which is good
        const float Score = DistToFlee - Dot * 1000.f;

        if (Score > BestScore)
        {
            BestScore = Score;
            BestTarget = FleeLocation->GetActorLocation();
        }
    }

    if (!BestTarget.IsZero())
    {
        RequestMoveIfNeeded(BestTarget, 0.5f, FleeMoveRequestCooldown, true);
    }
}

void ASDTAIController::OnMoveToTarget()
{
    m_ReachedTarget = false;
}

void ASDTAIController::RotateTowards(const FVector& targetLocation)
{
    if (!targetLocation.IsZero())
    {
        FVector direction = targetLocation - GetPawn()->GetActorLocation();
        FRotator targetRotation = direction.Rotation();

        targetRotation.Yaw = FRotator::ClampAxis(targetRotation.Yaw);

        SetControlRotation(targetRotation);
    }
}

void ASDTAIController::SetActorLocation(const FVector& targetLocation)
{
    GetPawn()->SetActorLocation(targetLocation);
}

void ASDTAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
    Super::OnMoveCompleted(RequestID, Result);

    m_ReachedTarget = true;
}

void ASDTAIController::UpdatePlayerInteraction(float deltaTime)
{
    //finish jump before updating AI state
    if (AtJumpSegment)
        return;

    UWorld* World = GetWorld();
    if (!World)
        return;

    UpdateAITickRate();

    const float Now = World->GetTimeSeconds();
    const bool bVisibleRelevant = IsRelevantToPlayerView();
    const float PerceptionInterval = bVisibleRelevant ? PerceptionUpdateVisible : PerceptionUpdateHidden;

    if (Now < m_NextPerceptionUpdateTime)
        return;

    m_NextPerceptionUpdateTime = Now + PerceptionInterval;

    APawn* selfPawn = GetPawn();
    if (!selfPawn)
        return;

    ACharacter* playerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    if (!playerCharacter)
        return;

    FVector detectionStartLocation = selfPawn->GetActorLocation() + selfPawn->GetActorForwardVector() * m_DetectionCapsuleForwardStartingOffset;
    FVector detectionEndLocation = detectionStartLocation + selfPawn->GetActorForwardVector() * m_DetectionCapsuleHalfLength * 2;

    TArray<TEnumAsByte<EObjectTypeQuery>> detectionTraceObjectTypes;
    detectionTraceObjectTypes.Add(UEngineTypes::ConvertToObjectType(COLLISION_PLAYER));

    TArray<FHitResult> allDetectionHits;
    GetWorld()->SweepMultiByObjectType(allDetectionHits, detectionStartLocation, detectionEndLocation, FQuat::Identity, detectionTraceObjectTypes, FCollisionShape::MakeSphere(m_DetectionCapsuleRadius));

    FHitResult detectionHit;
    GetHightestPriorityDetectionHit(allDetectionHits, detectionHit);

    UpdatePlayerInteractionBehavior(detectionHit, deltaTime);

    if (GetMoveStatus() == EPathFollowingStatus::Idle)
    {
        m_ReachedTarget = true;
    }

    FString debugString = "";

    switch (m_PlayerInteractionBehavior)
    {
    case PlayerInteractionBehavior_Chase:
        debugString = "Chase";
        break;
    case PlayerInteractionBehavior_Flee:
        debugString = "Flee";
        break;
    case PlayerInteractionBehavior_Collect:
        debugString = "Collect";
        break;
    }
}

bool ASDTAIController::HasLoSOnHit(const FHitResult& hit)
{
    if (!hit.GetComponent())
        return false;

    TArray<TEnumAsByte<EObjectTypeQuery>> TraceObjectTypes;
    TraceObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic));

    FVector hitDirection = hit.ImpactPoint - hit.TraceStart;
    hitDirection.Normalize();

    FHitResult losHit;
    FCollisionQueryParams queryParams = FCollisionQueryParams();
    queryParams.AddIgnoredActor(hit.GetActor());

    GetWorld()->LineTraceSingleByObjectType(losHit, hit.TraceStart, hit.ImpactPoint + hitDirection, TraceObjectTypes, queryParams);

    return losHit.GetActor() == nullptr;
}

void ASDTAIController::AIStateInterrupted()
{
    StopMovement();

    m_ReachedTarget = false;
    AtJumpSegment = false;
    InAir = false;

    if (UBlackboardComponent* BB = GetBlackboardComponent())
    {
        BB->SetValueAsBool(TEXT("m_ReachedTarget"), false);
        BB->SetValueAsBool(TEXT("IsJumping"), false);
        BB->SetValueAsBool(TEXT("IsChasing"), false);
        BB->SetValueAsBool(TEXT("IsFleeing"), false);
    }

    RunBehaviorTree(BehaviorTreeAsset);
  
}

ASDTAIController::PlayerInteractionBehavior ASDTAIController::GetCurrentPlayerInteractionBehavior(const FHitResult& hit)
{
    if (m_PlayerInteractionBehavior == PlayerInteractionBehavior_Collect)
    {
        if (!hit.GetComponent())
            return PlayerInteractionBehavior_Collect;

        if (hit.GetComponent()->GetCollisionObjectType() != COLLISION_PLAYER)
            return PlayerInteractionBehavior_Collect;

        if (!HasLoSOnHit(hit))
            return PlayerInteractionBehavior_Collect;

        return SDTUtils::IsPlayerPoweredUp(GetWorld()) ? PlayerInteractionBehavior_Flee : PlayerInteractionBehavior_Chase;
    }
    else
    {
        PlayerInteractionLoSUpdate();

        return SDTUtils::IsPlayerPoweredUp(GetWorld()) ? PlayerInteractionBehavior_Flee : PlayerInteractionBehavior_Chase;
    }
}

void ASDTAIController::GetHightestPriorityDetectionHit(const TArray<FHitResult>& hits, FHitResult& outDetectionHit)
{
    for (const FHitResult& hit : hits)
    {
        if (UPrimitiveComponent* component = hit.GetComponent())
        {
            if (component->GetCollisionObjectType() == COLLISION_PLAYER)
            {
                //we can't get more important than the player
                outDetectionHit = hit;
                return;
            }
            else if(component->GetCollisionObjectType() == COLLISION_COLLECTIBLE)
            {
                outDetectionHit = hit;
            }
        }
    }
}

void ASDTAIController::UpdatePlayerInteractionBehavior(const FHitResult& detectionHit, float deltaTime)
{
    PlayerInteractionBehavior currentBehavior = GetCurrentPlayerInteractionBehavior(detectionHit);

    if (currentBehavior != m_PlayerInteractionBehavior)
    {
        m_PlayerInteractionBehavior = currentBehavior;
        AIStateInterrupted();
		UpdateGroupMembership(); // met à jour l'appartenance au groupe à chaque transition																					 
    }
}

ASDTChaseGroup* ASDTAIController::GetOrCreateChaseGroup()
{
    if (m_CachedChaseGroup.IsValid())
        return m_CachedChaseGroup.Get();

    m_CachedChaseGroup = ASDTChaseGroup::GetInstance(GetWorld());
    return m_CachedChaseGroup.Get();
}

void ASDTAIController::UpdateGroupMembership()
{
    ASDTChaseGroup* Group = GetOrCreateChaseGroup();
    if (!Group)
        return;

    if (m_PlayerInteractionBehavior == PlayerInteractionBehavior_Chase)
    {
        // Rejoint le groupe si pas déjà membre
        Group->AddMember(this);
    }
    else
    {
        // Quitte le groupe si l'agent n'est plus en poursuite
        Group->RemoveMember(this);
    }
}

void ASDTAIController::OnGroupDissolved()
{
    // Le groupe vient d'être dissous : retour en Collect
    if (m_PlayerInteractionBehavior != PlayerInteractionBehavior_Collect)
    {
        AIStateInterrupted();
        m_PlayerInteractionBehavior = PlayerInteractionBehavior_Collect;
    }
}

bool ASDTAIController::IsRelevantToPlayerView() const
{
    APawn* SelfPawn = GetPawn();
    UWorld* World = GetWorld();
    if (!SelfPawn || !World)
        return false;

    APlayerController* PC = UGameplayStatics::GetPlayerController(World, 0);
    if (!PC)
        return false;

    APlayerCameraManager* CamMgr = PC->PlayerCameraManager;
    if (!CamMgr)
        return false;

    const FVector ToAI = SelfPawn->GetActorLocation() - CamMgr->GetCameraLocation();
    const float DistSq = ToAI.SizeSquared();

    // Far agents get reduced updates even if technically in front
    if (DistSq > FMath::Square(2500.f))
        return false;

    const FVector CamForward = CamMgr->GetCameraRotation().Vector();
    const FVector DirToAI = ToAI.GetSafeNormal();

    return FVector::DotProduct(CamForward, DirToAI) > 0.2f;
}

void ASDTAIController::UpdateAITickRate()
{
    PrimaryActorTick.TickInterval = IsRelevantToPlayerView() ? VisibleTickInterval : HiddenTickInterval;
}

bool ASDTAIController::ShouldIssueMoveRequest(const FVector& NewTarget, float Cooldown) const
{
    UWorld* World = GetWorld();
    if (!World)
        return false;

    const float Now = World->GetTimeSeconds();

    if (!m_HasRequestedMove)
        return true;

    if (Now >= m_NextMoveRequestTime)
        return true;

    return FVector::DistSquared(NewTarget, m_LastRequestedMoveTarget) > TargetRefreshDistSq;
}

void ASDTAIController::RequestMoveIfNeeded(const FVector& Target, float AcceptanceRadius, float Cooldown, bool bUsePathfinding)
{
    UWorld* World = GetWorld();
    if (!World)
        return;

    if (!ShouldIssueMoveRequest(Target, Cooldown))
        return;

    MoveToLocation(Target, AcceptanceRadius, false, bUsePathfinding, true, false, nullptr, false);
    OnMoveToTarget();

    m_LastRequestedMoveTarget = Target;
    m_HasRequestedMove = true;
    m_NextMoveRequestTime = World->GetTimeSeconds() + Cooldown;
}