// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "MyBTTask_IsPlayerPoweredUp.generated.h"

/**
 * Check if player is powered up
 */
UCLASS()
class SOFTDESIGNTRAINING_API UMyBTTask_IsPlayerPoweredUp : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
