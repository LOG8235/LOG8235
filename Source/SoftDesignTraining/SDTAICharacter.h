// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SoftDesignTrainingCharacter.h"
#include "SDTAICharacter.generated.h"

UCLASS()
class SOFTDESIGNTRAINING_API ASDTAICharacter : public ASoftDesignTrainingCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASDTAICharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void TickMove(float DeltaTime);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement")
	float MaxSpeed = 600.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float Acceleration = 1200.f;

	FVector CurrentVelocity = FVector::ZeroVector;

	FVector DesiredDir = FVector::ForwardVector;

};
