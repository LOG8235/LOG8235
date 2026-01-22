// Fill out your copyright notice in the Description page of Project Settings.


#include "SDTAICharacter.h"
#include "DrawDebugHelpers.h"
#include "Components/CapsuleComponent.h"
#include "Engine/World.h"
#include "Engine/EngineTypes.h"
#include "Engine/OverlapResult.h"
#include "GameFramework/CharacterMovementComponent.h"
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
