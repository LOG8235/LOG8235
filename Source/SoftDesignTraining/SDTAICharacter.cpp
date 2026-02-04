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
    if (ComputeFlee(DeltaTime, SpeedScale))
    {}
    else if (ComputePursuit())
    {}
    else if (DetectCollectible())
    {}
    else {ComputeObstacleAvoidance(DeltaTime, SpeedScale);
    }
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
    //CurrentVelocity += DesiredDir * Acceleration * DeltaTime;

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


bool ASDTAICharacter::ComputeObstacleAvoidance(float DeltaTime, float& OutSpeedScale)
{
    const FVector Start = GetActorLocation() + FVector(0, 0, 0.f);
    const FVector Forward = DesiredDir.GetSafeNormal();
    const FVector End = Start + Forward * WallDetectionDistance;

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

    ECollisionChannel objectType = ECC_WorldStatic;
    float MinHitDist = FLT_MAX;
    for (const FHitResult& H : WallHits)
    {
        MinHitDist = FMath::Min(MinHitDist, H.Distance);
		objectType = H.GetComponent()->GetCollisionObjectType();
    }
	/*float speedScale = (MinHitDist + 0.01f) / WallDetectionDistance;
    OutSpeedScale = speedScale / WallDetectionDistance < 0.1f ? 0.1f : speedScale;*/
    float MinSpeedScale = 0.2f;
    float DistanceRatio = FMath::Clamp(MinHitDist / WallDetectionDistance, MinSpeedScale, 1.0f);


    if (objectType == COLLISION_DEATH_OBJECT)
    {
        OutSpeedScale = (DistanceRatio <= MinSpeedScale) ? 0.0f : DistanceRatio;
    }
    else
    {
        OutSpeedScale = DistanceRatio;
    }
   

    const float ProbeAngle = 90.f; 
    const FVector LeftDir = DesiredDir.RotateAngleAxis(ProbeAngle, FVector::UpVector).GetSafeNormal();
    const FVector RightDir = DesiredDir.RotateAngleAxis(-ProbeAngle, FVector::UpVector).GetSafeNormal();

    TArray<FHitResult> HitsLeft;
    TArray<FHitResult> HitsRight;
    const FVector LeftEnd = Start + LeftDir * WallDetectionDistance * 0.2f;
    const FVector RightEnd = Start + RightDir * WallDetectionDistance * 0.2f;

    GetWorld()->SweepMultiByObjectType(HitsLeft, Start, LeftEnd, FQuat::Identity, ECC_WorldStatic, shape, Params);
    GetWorld()->SweepMultiByObjectType(HitsRight, Start, RightEnd, FQuat::Identity, ECC_WorldStatic, shape, Params);

    if (bDrawWallDebug)
    {
        DrawDebugCapsule(GetWorld(), LeftEnd, CapsuleHalfHeight, CapsuleRadius, FQuat::Identity, HitsLeft.Num() == 0 ? FColor::Red : FColor::Green, false, 0.05f, 0, 1.f);
        DrawDebugCapsule(GetWorld(), RightEnd, CapsuleHalfHeight, CapsuleRadius, FQuat::Identity, HitsRight.Num() == 0 ? FColor::Red : FColor::Green, false, 0.05f, 0, 1.f);
    }

    bool bLeftBlocked = (HitsLeft.Num() > 0);
    bool bRightBlocked = (HitsRight.Num() > 0);

    if (!bLeftBlocked && bRightBlocked)
    {
		AvoidTurnRateDegPerSec = FMath::Abs(AvoidTurnRateDegPerSec);
    }
    else if(bLeftBlocked && !bRightBlocked)
    {
        
		AvoidTurnRateDegPerSec = -FMath::Abs(AvoidTurnRateDegPerSec);
    }
    float TurnAngle = AvoidTurnRateDegPerSec * DeltaTime;
    DesiredDir = DesiredDir.RotateAngleAxis(TurnAngle, FVector::UpVector).GetSafeNormal();
    DesiredDir.Z = 0.f;
    DesiredDir.Normalize();

    return true;
	
}


bool ASDTAICharacter::ComputePursuit()  {
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

    if (!HasClearPathTo(Player->GetActorLocation()))
        return false;

    FVector Dir = Player->GetActorLocation() - Center;
    Dir.Z = 0.f;

    if (!Dir.Normalize())
        return false;

    DesiredDir = Dir;

    return true;
}

bool ASDTAICharacter::HasClearPathTo(FVector End) const {

    const FVector Start = GetActorLocation();


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

    return WallHits.IsEmpty();
}

bool ASDTAICharacter::ComputeFlee(float DeltaTime, float& OutSpeedScale)  {
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
       
    float Alpha = 10.f* DeltaTime;

    if ((GetActorLocation() - Player->GetActorLocation()).SizeSquared() < FMath::Square(playerDetectionRadius * 0.25f)) {
		DesiredDir = Away.GetSafeNormal();
	}else {
        DesiredDir = FMath::Lerp(DesiredDir, Away, Alpha).GetSafeNormal();
    }

    /*OutSpeedScale = 1.0f;*/
    ComputeObstacleAvoidance(DeltaTime, OutSpeedScale);

    return true;
	
}


bool ASDTAICharacter::DetectCollectible() {

    TArray<FOverlapResult> Overlaps;
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(this);

    FCollisionObjectQueryParams Obj;
    Obj.AddObjectTypesToQuery(COLLISION_COLLECTIBLE);

    const FVector Center = GetActorLocation() + (GetActorForwardVector() * collectibleDetectionRadius);
    const FCollisionShape Sphere = FCollisionShape::MakeSphere(collectibleDetectionRadius);

    const bool hit = GetWorld()->OverlapMultiByObjectType(Overlaps, Center, FQuat::Identity, Obj, Sphere, Params);
   
    if(bDrawCollectibleDebug)
        DrawDebugSphere(GetWorld(), Center, collectibleDetectionRadius, 20, hit ? FColor::Blue : FColor::Orange, false, 0.05f);


    if (!hit) {
        return false;
    }

    const ASDTCollectible* ClosestCollectible = nullptr;
    float MinDistanceSq = FLT_MAX; 

    for (const FOverlapResult& O : Overlaps)
    {
        const ASDTCollectible* CurrentCollectible = Cast<ASDTCollectible>(O.GetActor());

        if (CurrentCollectible->GetStaticMeshComponent()->IsVisible() && HasClearPathTo(CurrentCollectible->GetActorLocation()))
        {
            float DistSq = FVector::DistSquared(GetActorLocation(), CurrentCollectible->GetActorLocation());

            
            if (DistSq <= MinDistanceSq)
            {
                MinDistanceSq = DistSq;
                ClosestCollectible = CurrentCollectible;
            }
        }
    }

    if (!ClosestCollectible)
        return false;

    FVector Dir = ClosestCollectible->GetActorLocation() - GetActorLocation();
    Dir.Z = 0.f;

    if (!Dir.Normalize())
        return false;

    DesiredDir = Dir;

    return true;
}