// Fill out your copyright notice in the Description page of Project Settings.

#include "SDTAIController.h"
#include "SDTChaseGroup.h"
#include "SoftDesignTraining.h"
#include "SDTCollectible.h"
#include "SDTFleeLocation.h"
#include "SDTPathFollowingComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetMathLibrary.h"
//#include "UnrealMathUtility.h"
#include "SDTUtils.h"
#include "EngineUtils.h"
#include "BehaviorTree/BlackboardComponent.h"

ASDTAIController::ASDTAIController(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer.SetDefaultSubobjectClass<USDTPathFollowingComponent>(TEXT("PathFollowingComponent")))
{
    m_PlayerInteractionBehavior = PlayerInteractionBehavior_Collect;
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
    float closestSqrCollectibleDistance = 18446744073709551610.f;
    ASDTCollectible* closestCollectible = nullptr;

    TArray<AActor*> foundCollectibles;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASDTCollectible::StaticClass(), foundCollectibles);

    while (foundCollectibles.Num() != 0)
    {
        int index = FMath::RandRange(0, foundCollectibles.Num() - 1);

        ASDTCollectible* collectibleActor = Cast<ASDTCollectible>(foundCollectibles[index]);
        if (!collectibleActor)
            return;

        if (!collectibleActor->IsOnCooldown())
        {
            MoveToLocation(foundCollectibles[index]->GetActorLocation(), 0.5f, false, true, true, false, NULL, false);
            OnMoveToTarget();
            return;
        }
        else
        {
            foundCollectibles.RemoveAt(index);
        }
    }
}

void ASDTAIController::MoveToPlayer()
{
    ACharacter* playerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    if (!playerCharacter)
        return;

    MoveToActor(playerCharacter, 0.5f, false, true, true, NULL, false);
    OnMoveToTarget();
}

void ASDTAIController::MoveToEncirclementPosition()
{
    ASDTChaseGroup* Group = GetOrCreateChaseGroup();

    APawn* SelfPawn = GetPawn();
    ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    if (!SelfPawn || !PlayerCharacter)
        return;

    float DistanceToPlayer = FVector::Dist(SelfPawn->GetActorLocation(), PlayerCharacter->GetActorLocation());

    // Si pas encore de LKP valide ou groupe d'un seul membre : poursuite directe
    if (!Group || !Group->HasValidLKP() || Group->GetMemberCount() <= 1 || DistanceToPlayer <= 550)
    {
        MoveToPlayer();
        return;
    }

    // Récupère la position d'encerclement assignée à cet agent
    FVector TargetPos = Group->GetEncirclementPositionFor(this);

    MoveToLocation(TargetPos, 0.5f, false, true, true, false, NULL, false);
    OnMoveToTarget();
}


void ASDTAIController::PlayerInteractionLoSUpdate()
{
    ACharacter* playerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
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
        //m_PlayerInteractionBehavior = PlayerInteractionBehavior_Collect;
        UpdateGroupMembership();
    }
}

void ASDTAIController::MoveToBestFleeLocation()
{
    float bestLocationScore = 0.f;
    ASDTFleeLocation* bestFleeLocation = nullptr;

    ACharacter* playerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    if (!playerCharacter)
        return;

    for (TActorIterator<ASDTFleeLocation> actorIterator(GetWorld(), ASDTFleeLocation::StaticClass()); actorIterator; ++actorIterator)
    {
        ASDTFleeLocation* fleeLocation = Cast<ASDTFleeLocation>(*actorIterator);
        if (fleeLocation)
        {
            float distToFleeLocation = FVector::Dist(fleeLocation->GetActorLocation(), playerCharacter->GetActorLocation());

            FVector selfToPlayer = playerCharacter->GetActorLocation() - GetPawn()->GetActorLocation();
            selfToPlayer.Normalize();

            FVector selfToFleeLocation = fleeLocation->GetActorLocation() - GetPawn()->GetActorLocation();
            selfToFleeLocation.Normalize();

            float fleeLocationToPlayerAngle = FMath::RadiansToDegrees(acosf(FVector::DotProduct(selfToPlayer, selfToFleeLocation)));
            float locationScore = distToFleeLocation + fleeLocationToPlayerAngle * 100.f;

            if (locationScore > bestLocationScore)
            {
                bestLocationScore = locationScore;
                bestFleeLocation = fleeLocation;
            }
        }
    }

    if (bestFleeLocation)
    {
        MoveToLocation(bestFleeLocation->GetActorLocation(), 0.5f, false, true, false, false, NULL, false);
        OnMoveToTarget();
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

void ASDTAIController::ShowNavigationPath()
{
    if (UPathFollowingComponent* pathFollowingComponent = GetPathFollowingComponent())
    {
        if (pathFollowingComponent->HasValidPath())
        {
            const FNavPathSharedPtr path = pathFollowingComponent->GetPath();
            TArray<FNavPathPoint> pathPoints = path->GetPathPoints();

            for (int i = 0; i < pathPoints.Num(); ++i)
            {
                if (i != 0 and m_PlayerInteractionBehavior == PlayerInteractionBehavior_Chase)
                {
                    DrawDebugLine(GetWorld(), pathPoints[i].Location, pathPoints[i - 1].Location, FColor::Yellow);
                }
            }
        }
    }
}

void ASDTAIController::UpdatePlayerInteraction(float deltaTime)
{
    m_AIUpdateAccumulator += deltaTime;

    if (m_AIUpdateAccumulator < m_AIUpdateInterval)
        return;

    m_AIUpdateAccumulator = 0.f;

    //finish jump before updating AI state
    if (AtJumpSegment)
        return;

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

        UE_LOG(LogTemp, Log, TEXT("GET CURRENT IF BEEF"));

        return SDTUtils::IsPlayerPoweredUp(GetWorld()) ? PlayerInteractionBehavior_Flee : PlayerInteractionBehavior_Chase;
    }
    else
    {
        PlayerInteractionLoSUpdate();

        UE_LOG(LogTemp, Log, TEXT("GET CURRENT ELSE BEEF"));

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
            else if (component->GetCollisionObjectType() == COLLISION_COLLECTIBLE)
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
    return ASDTChaseGroup::GetInstance(GetWorld());
}

void ASDTAIController::UpdateGroupMembership()
{
    ASDTChaseGroup* Group = GetOrCreateChaseGroup();
    if (!Group)
        return;

    if (m_PlayerInteractionBehavior == PlayerInteractionBehavior_Chase)
    {
        Group->AddMember(this);
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