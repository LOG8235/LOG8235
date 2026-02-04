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


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MaxSpeed = 600.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float Acceleration = 1200.f;

	UPROPERTY(EditAnywhere, Category = "AI|Wall Avoidance")
	float WallDetectionDistance = 300.f;

	UPROPERTY(EditAnywhere, Category = "AI|Wall Avoidance")
	float AvoidTurnRateDegPerSec = 90.f;

	UPROPERTY(EditAnywhere, Category = "AI|Wall Avoidance")
	bool bDrawWallDebug = true;

	UPROPERTY(EditAnywhere, Category = "AI|Player Chase")
	float playerDetectionRadius = 700.f;
	UPROPERTY(EditAnywhere, Category = "AI|Collectible Chase")
	float collectibleDetectionRadius = 350.f;

	UPROPERTY(EditAnywhere, Category = "AI|Player Chase")
	bool bDrawPursuitDebug = true;

	UPROPERTY(EditAnywhere, Category = "AI|Collectible Chase")
	bool bDrawCollectibleDebug = true;

	bool bIsDoingUTurn = false;
	FVector UTurnDirection = FVector::ZeroVector;
	void TickMove(float DeltaTime, float SpeedScale);
	bool ComputeObstacleAvoidance(float DeltaTime, float& OutSpeedScale);
	bool ComputePursuit();
	bool DetectCollectible();
	bool HasClearPathTo(FVector End) const;
	bool ComputeFlee(float DeltaTime, float& OutSpeedScale);

	FVector CurrentVelocity = FVector::ZeroVector;

	FVector DesiredDir = FVector::ForwardVector;

};