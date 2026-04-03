// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "MyBTService_GetMReachedAndJump.generated.h"

/**
 * 
 */
UCLASS()
class SOFTDESIGNTRAINING_API UMyBTService_GetMReachedAndJump : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UMyBTService_GetMReachedAndJump();

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

protected:
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector ReachedTargetKey;

	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector IsJumpingKey;
};
