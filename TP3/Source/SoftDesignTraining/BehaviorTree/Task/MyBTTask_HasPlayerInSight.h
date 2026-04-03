// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlueprintBase.h"
#include "MyBTTask_HasPlayerInSight.generated.h"

/**
 * Check if player is in sight using line trace
 */
UCLASS()
class SOFTDESIGNTRAINING_API UMyBTTask_HasPlayerInSight : public UBTTask_BlueprintBase
{
	GENERATED_BODY()

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
