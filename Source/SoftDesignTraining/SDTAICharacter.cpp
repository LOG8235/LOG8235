// Fill out your copyright notice in the Description page of Project Settings.


#include "SDTAICharacter.h"

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
    TickMove(DeltaTime);
    UE_LOG(LogTemp, Warning, TEXT("Speed: %f"), CurrentVelocity.Size());
}

// Called to bind functionality to input
void ASDTAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ASDTAICharacter::TickMove(float DeltaTime) {
    DesiredDir = DesiredDir.GetSafeNormal();

    CurrentVelocity += DesiredDir * Acceleration * DeltaTime;

    const float Speed = CurrentVelocity.Size();
    if (Speed > MaxSpeed)
    {
        CurrentVelocity = CurrentVelocity.GetSafeNormal() * MaxSpeed;
    }

    AddActorWorldOffset(CurrentVelocity * DeltaTime, true);

    if (!CurrentVelocity.IsNearlyZero())
    {
        const FRotator TargetRot = CurrentVelocity.ToOrientationRotator();
        SetActorRotation(TargetRot);
    }
}

