// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_UpdateChase.generated.h"

/**
 *
 */
UCLASS()
class UBTService_UpdateChase : public UBTService
{
    GENERATED_BODY()

public:
    UBTService_UpdateChase();

protected:
    virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};