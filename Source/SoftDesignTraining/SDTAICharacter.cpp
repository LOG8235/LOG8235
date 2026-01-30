// Fill out your copyright notice in the Description page of Project Settings.


#include "SDTAICharacter.h"
#include "DrawDebugHelpers.h"
#include "Components/CapsuleComponent.h"
#include "Engine/World.h"
#include "Engine/EngineTypes.h"
#include "Engine/OverlapResult.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SoftDesignTrainingMainCharacter.h"
#include "SDTUtils.h"
#include "SDTCollectible.h"


// Sets default values
ASDTAICharacter::ASDTAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASDTAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASDTAICharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    float SpeedScale = 1.f;
    float TempScale = 1.f;
    FVector NewDir = DesiredDir;
    if (SDTUtils::IsPlayerPoweredUp(GetWorld()))
    {
        if (ComputeFlee(DeltaTime, NewDir, SpeedScale)) DesiredDir = NewDir;
    }
    else if (ComputePursuit(NewDir))
    {
        DesiredDir = NewDir;
        ComputeObstacleAvoidance(DeltaTime, DesiredDir, TempScale);

        TickMove(DeltaTime, SpeedScale);
        return;

    }
    /*else if (DetectCollectible(NewDir))
    {

        DesiredDir = NewDir;

    */
    if (ComputeObstacleAvoidance(DeltaTime, NewDir, SpeedScale)) DesiredDir = NewDir;

    TickMove(DeltaTime, SpeedScale);
}

void ASDTAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}


//Pour faire bouger les AI avec une vitesse maximale et une vitesse qui scale
void ASDTAICharacter::TickMove(float DeltaTime, float SpeedScale) {

    DesiredDir.Z = 0.f;
    DesiredDir = DesiredDir.GetSafeNormal();

    CurrentVelocity += DesiredDir * Acceleration * DeltaTime;

    const float AllowedMax = MaxSpeed * SpeedScale;
    if (UCharacterMovementComponent* MoveComp = GetCharacterMovement())
    {
        MoveComp->MaxWalkSpeed = MaxSpeed * SpeedScale;
    }

    AddMovementInput(DesiredDir, 1.0f);

    if (!DesiredDir.IsNearlyZero())
    {
        const float Yaw = DesiredDir.ToOrientationRotator().Yaw;
        SetActorRotation(FRotator(0.f, Yaw, 0.f));
    }
}


bool ASDTAICharacter::ComputeObstacleAvoidance(float DeltaTime, FVector& InOutDir, float& OutSpeedScale)
{
    const FVector Start = GetActorLocation() + FVector(0, 0, 0.f);
    const FVector Forward = InOutDir.GetSafeNormal();
    const FVector End = Start + Forward * WallTraceDistance;

    FCollisionShape shape;
    TArray<FHitResult> WallHits;
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(this);

    FCollisionObjectQueryParams Obstacles;
    Obstacles.AddObjectTypesToQuery(ECC_WorldStatic);
    Obstacles.AddObjectTypesToQuery(COLLISION_DEATH_OBJECT);

    const float CapsuleRadius = GetCapsuleComponent()->GetScaledCapsuleRadius();
    const float CapsuleHalfHeight = GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
    shape.SetCapsule(CapsuleRadius, CapsuleHalfHeight);

    GetWorld()->SweepMultiByObjectType(WallHits, Start, End, FQuat::Identity, Obstacles, shape, Params);

    if (bDrawWallDebug) DrawDebugCapsule(GetWorld(), End, CapsuleHalfHeight, CapsuleRadius, FQuat::Identity, WallHits.Num() == 0 ? FColor::Red : FColor::Green, false, 0.05f, 0, 2.f);

    if (WallHits.Num() == 0) return false;

    float MinHitDist = FLT_MAX;
    for (const FHitResult& H : WallHits)
    {
        MinHitDist = FMath::Min(MinHitDist, H.Distance);
    }

    OutSpeedScale = (MinHitDist < 70.f) ? MinSpeedScaleNearDeathFloor : OutSpeedScale;

    float TurnAngle = AvoidTurnRateDegPerSec * DeltaTime;

    const float ProbeAngle = 40.f; 
    const FVector LeftTry = InOutDir.RotateAngleAxis(ProbeAngle, FVector::UpVector).GetSafeNormal();
    const FVector RightTry = InOutDir.RotateAngleAxis(-ProbeAngle, FVector::UpVector).GetSafeNormal();

    TArray<FHitResult> HitsLeft;
    TArray<FHitResult> HitsRight;
    const FVector LeftEnd = Start + LeftTry * WallTraceDistance * 0.6;
    const FVector RightEnd = Start + RightTry * WallTraceDistance * 0.6;

    GetWorld()->SweepMultiByObjectType(HitsLeft, Start, LeftEnd, FQuat::Identity, ECC_WorldStatic, shape, Params);
    GetWorld()->SweepMultiByObjectType(HitsRight, Start, RightEnd, FQuat::Identity, ECC_WorldStatic, shape, Params);

    if (bDrawWallDebug)
    {
        DrawDebugCapsule(GetWorld(), LeftEnd, CapsuleHalfHeight, CapsuleRadius, FQuat::Identity, HitsLeft.Num() == 0 ? FColor::Green : FColor::Red, false, 0.05f, 0, 1.f);
        DrawDebugCapsule(GetWorld(), RightEnd, CapsuleHalfHeight, CapsuleRadius, FQuat::Identity, HitsRight.Num() == 0 ? FColor::Green : FColor::Red, false, 0.05f, 0, 1.f);
    }

    bool bFrontBlocked = (WallHits.Num() > 0);
    bool bLeftBlocked = (HitsLeft.Num() > 0);
    bool bRightBlocked = (HitsRight.Num() > 0);

    if (bFrontBlocked && bLeftBlocked && bRightBlocked && !bIsDoingUTurn)
    {
        bIsDoingUTurn = true;
        UTurnDirection = -InOutDir;
    }

    if (bIsDoingUTurn)
    {
        // U turn marche pas avec 3 death floor jsp pq
        float RotationStep = AvoidTurnRateDegPerSec * DeltaTime * 5.0f;
        InOutDir = InOutDir.RotateAngleAxis(RotationStep, FVector::UpVector).GetSafeNormal();

        OutSpeedScale = MinSpeedScaleNearDeathFloor;

        TArray<FHitResult> ClearCheck;
        GetWorld()->SweepMultiByObjectType(ClearCheck, Start, Start + InOutDir * WallTraceDistance, FQuat::Identity, Obstacles, shape, Params);

        if (ClearCheck.Num() == 0)
        {
            bIsDoingUTurn = false;
        }
        return true;
    }

    if (HitsLeft.Num() == 0 && HitsRight.Num() > 0)
    {
        InOutDir = InOutDir.RotateAngleAxis(TurnAngle, FVector::UpVector).GetSafeNormal();
    }
    else if (HitsRight.Num() == 0 && HitsLeft.Num() > 0)
    {
        InOutDir = InOutDir.RotateAngleAxis(-TurnAngle, FVector::UpVector).GetSafeNormal();
    }
    else if (HitsLeft.Num() > 0 && HitsRight.Num() > 0)
    {
        InOutDir = InOutDir.RotateAngleAxis(-TurnAngle, FVector::UpVector).GetSafeNormal();
    }
 
    InOutDir.Z = 0.f;
    InOutDir.Normalize();

    return true;
	
}

bool ASDTAICharacter::ComputePursuit(FVector& OutDesiredDir) const {
    if (SDTUtils::IsPlayerPoweredUp(GetWorld())) {
        return false;
    }

    TArray<FOverlapResult> Overlaps;
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(this);

    FCollisionObjectQueryParams Obj;
    Obj.AddObjectTypesToQuery(COLLISION_PLAYER);
    
    const FVector Center = GetActorLocation();
    const FCollisionShape Sphere = FCollisionShape::MakeSphere(playerDetectionRadius);

    const bool bAny = GetWorld()->OverlapMultiByObjectType(Overlaps, Center, FQuat::Identity, Obj, Sphere, Params);

    if (bDrawPursuitDebug) {
        DrawDebugSphere(GetWorld(), Center, playerDetectionRadius, 20, bAny ? FColor::Green : FColor::Red, false, 0.05f);
    }

    if (!bAny) {
        return false;
    }

    const ASoftDesignTrainingMainCharacter* Player = nullptr;

    for (const FOverlapResult& O : Overlaps)
    {
        Player = Cast<ASoftDesignTrainingMainCharacter>(O.GetActor());
        if (Player)
            break;
    }

    if (!Player)
        return false;

    if (!HasClearPathTo(Player))
        return false;

    FVector Dir = Player->GetActorLocation() - Center;
    Dir.Z = 0.f;

    if (!Dir.Normalize())
        return false;

    OutDesiredDir = Dir;

    return true;
}

bool ASDTAICharacter::HasClearPathTo(const AActor* Target) const {
    if (!Target) return false;

    const FVector Start = GetActorLocation();
    const FVector End = Target->GetActorLocation();

    FHitResult Hit;
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(this);
    Params.AddIgnoredActor(Target);

    FCollisionObjectQueryParams Obj;
    Obj.AddObjectTypesToQuery(ECC_WorldStatic);
    Obj.AddObjectTypesToQuery(COLLISION_DEATH_OBJECT);

    const bool bHit = GetWorld()->LineTraceSingleByObjectType(Hit, Start, End, Obj, Params);

    if (bDrawPursuitDebug) {
        DrawDebugLine(GetWorld(), Start, End, bHit ? FColor::Red : FColor::Green, false, 5.f, 0, 2.f);
    }

    return !bHit;
}

bool ASDTAICharacter::ComputeFlee(float DeltaTime, FVector& OutDesiredDir, float& OutSpeedScale) const {
    if (!SDTUtils::IsPlayerPoweredUp(GetWorld())) {
        return false;
    }

    TArray<FOverlapResult> Overlaps;
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(this);

    const FVector Center = GetActorLocation();
    const FCollisionShape CollisionShape = FCollisionShape::MakeSphere(playerDetectionRadius);

    const bool bAny = GetWorld()->OverlapMultiByObjectType(Overlaps, Center, FQuat::Identity, COLLISION_PLAYER, CollisionShape, Params);

    if (bDrawPursuitDebug) DrawDebugSphere(GetWorld(), Center, playerDetectionRadius, 20, bAny ? FColor::Green : FColor::Red, false, 0.05f);

    if (GFrameCounter % 25 == 0) {
        if (!bAny) return false;

        const ASoftDesignTrainingMainCharacter* Player = nullptr;
        for (const FOverlapResult& O : Overlaps) {
            Player = Cast<ASoftDesignTrainingMainCharacter>(O.GetActor());
            if (Player) break;
        }

        if (!Player) return false;

        FVector Away = GetActorLocation() - Player->GetActorLocation();
        Away.Z = 0.f;

        if (!Away.Normalize()) return false;

        OutDesiredDir = Away;

        return true;
	}
	else return false;
}

bool ASDTAICharacter::IsDirectionFree(const FVector& Dir, float Distance) const {
    const FVector Start = GetActorLocation();
    const FVector End = Start + Dir.GetSafeNormal() * Distance;

    FCollisionShape shape;

    TArray<FHitResult> Hits;
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(this);

    FCollisionObjectQueryParams ObjectQueryParams;
    ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldStatic);
    ObjectQueryParams.AddObjectTypesToQuery(COLLISION_DEATH_OBJECT);

    const float CapsuleRadius = GetCapsuleComponent()->GetScaledCapsuleRadius();
    const float CapsuleHalfHeight = GetCapsuleComponent()->GetScaledCapsuleHalfHeight();

    shape.SetCapsule(CapsuleRadius, CapsuleHalfHeight);

    return GetWorld()->SweepMultiByObjectType(Hits, Start, End, FQuat::Identity, ObjectQueryParams, shape, Params);
}

bool ASDTAICharacter::DetectCollectible(FVector& OutDesiredDir) const {

    TArray<FOverlapResult> Overlaps;
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(this);

    FCollisionObjectQueryParams Obj;
    Obj.AddObjectTypesToQuery(COLLISION_COLLECTIBLE);

    const FVector Center = GetActorLocation() + (GetActorForwardVector() * playerDetectionRadius);
    const FCollisionShape Sphere = FCollisionShape::MakeSphere(playerDetectionRadius);

    const bool bAny = GetWorld()->OverlapMultiByObjectType(Overlaps, Center, FQuat::Identity, Obj, Sphere, Params);

    if (bDrawPursuitDebug) {
        DrawDebugSphere(GetWorld(), Center, playerDetectionRadius, 20, bAny ? FColor::Blue : FColor::Orange, false, 0.05f);
    }

    if (!bAny) {
        return false;
    }

    const ASDTCollectible* ClosestCollectible = nullptr;
    float MinDistanceSq = FLT_MAX; 

    for (const FOverlapResult& O : Overlaps)
    {
        const ASDTCollectible* CurrentCollectible = Cast<ASDTCollectible>(O.GetActor());

        if (CurrentCollectible && HasClearPathTo(CurrentCollectible))
        {
            float DistSq = FVector::DistSquared(Center, CurrentCollectible->GetActorLocation());

            
            if (DistSq < MinDistanceSq)
            {
                MinDistanceSq = DistSq;
                ClosestCollectible = CurrentCollectible;
            }
        }
    }

    if (!ClosestCollectible)
        return false;

    FVector Dir = ClosestCollectible->GetActorLocation() - Center;
    Dir.Z = 0.f;

    if (!Dir.Normalize())
        return false;

    OutDesiredDir = Dir;

    return true;
}