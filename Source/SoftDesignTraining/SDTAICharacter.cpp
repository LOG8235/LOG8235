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
    FVector NewDir = DesiredDir;
    if (ComputePursuit(NewDir)) {
        DesiredDir = NewDir;
    }
    ComputeWallAvoidance(DeltaTime, DesiredDir, SpeedScale);
    TickMove(DeltaTime, SpeedScale);
    UE_LOG(LogTemp, Warning, TEXT("Speed: %f"), CurrentVelocity.Size());
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


//Pour faire un check pour voir si un mur est proche
bool ASDTAICharacter::ComputeWallAvoidance(float DeltaTime, FVector& InOutDir, float& OutSpeedScale) const
{
    OutSpeedScale = 1.f;

    const FVector Start = GetActorLocation() + FVector(0, 0, 0.f);
    const FVector Forward = InOutDir.GetSafeNormal();
    const FVector End = Start + Forward * WallTraceDistance;

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

    GetWorld()->SweepMultiByObjectType(
        Hits,
        Start,
        End,
        FQuat::Identity,
        ObjectQueryParams,
        shape,
        Params
    );


    if (bDrawWallDebug)
    {
        DrawDebugCapsule(GetWorld(), End, CapsuleHalfHeight, CapsuleRadius, FQuat::Identity, Hits.Num() == 0 ? FColor::Red : FColor::Green, false, 0.05f, 0, 2.f);
    }
    OutSpeedScale = MinSpeedScaleNearWall;

    if (Hits.Num() == 0)
        return false;

    OutSpeedScale = 0.2f;

    const float TurnAngle = AvoidTurnRateDegPerSec * DeltaTime;
    InOutDir = InOutDir.RotateAngleAxis(TurnAngle, FVector::UpVector);
    InOutDir.Z = 0.f;
    InOutDir.Normalize();

    return true;
}

bool ASDTAICharacter::ComputePursuit(FVector& OutDesiredDir) const {
    if (SDTUtils::IsPlayerPoweredUp(GetWorld())) {
        UE_LOG(LogTemp, Warning, TEXT("PLAYER IS POWERED UP!"));
        return false;
    }

    TArray<FOverlapResult> Overlaps;
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(this);

    FCollisionObjectQueryParams Obj;
    Obj.AddObjectTypesToQuery(COLLISION_PLAYER);
    
    const FVector Center = GetActorLocation();
    const FCollisionShape Sphere = FCollisionShape::MakeSphere(playerDetectionRadius);

    const bool bAny = GetWorld()->OverlapMultiByObjectType(
        Overlaps,
        Center,
        FQuat::Identity,
        Obj,
        Sphere,
        Params
    );

    if (bDrawPursuitDebug) {
        DrawDebugSphere(GetWorld(), Center, playerDetectionRadius, 20, bAny ? FColor::Green : FColor::Red, false, 0.05f);
    }

    if (!bAny) {
        UE_LOG(LogTemp, Warning, TEXT("Nothing found!!!!"));
        return false;
    }
    const AActor* BestTarget = nullptr;
    float BestDistSq = TNumericLimits<float>::Max();

    for (const FOverlapResult& O : Overlaps)
    {
        const AActor* A = O.GetActor();
        if (!A) {
            UE_LOG(LogTemp, Warning, TEXT("Actor NOT found"));
            continue;
        }
        UE_LOG(LogTemp, Warning, TEXT("Actor found: %s"), *A->GetActorNameOrLabel());
        const ASoftDesignTrainingMainCharacter* Player = Cast<ASoftDesignTrainingMainCharacter>(A);
        if (!Player) {
            UE_LOG(LogTemp, Warning, TEXT("Player NOT found!!!!"));
            continue;
        }
        UE_LOG(LogTemp, Warning, TEXT("Player found: %s"), *Player->GetActorNameOrLabel());
        UE_LOG(LogTemp, Warning, TEXT("Player Coordinates: %s"), *Player->GetActorLocation().ToString());

        const float D2 = FVector::DistSquared(Center, Player->GetActorLocation());
        if (D2 < BestDistSq)
        {
            BestDistSq = D2;
            BestTarget = Player;
        }
    }

    if (!BestTarget)
        return false;

    if (!HasClearPathTo(BestTarget))
        return false;

    OutDesiredDir = (BestTarget->GetActorLocation() - Center);
    UE_LOG(LogTemp, Warning, TEXT("Desired Dir: %s"), *OutDesiredDir.ToString());
    OutDesiredDir.Z = 0.f;
    OutDesiredDir = OutDesiredDir.GetSafeNormal();

    return !OutDesiredDir.IsNearlyZero();
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

    const bool bHit = GetWorld()->LineTraceSingleByObjectType(
        Hit,
        Start,
        End,
        Obj,
        Params
    );

    if (bDrawPursuitDebug) {
        DrawDebugLine(GetWorld(), Start, End, bHit ? FColor::Red : FColor::Green, false, 5.f, 0, 2.f);
    }

    return !bHit;
}
