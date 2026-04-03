// Fill out your copyright notice in the Description page of Project Settings.

#include "MyBTTask_IsPlayerPoweredUp.h"
#include "BehaviorTree/BlackboardComponent.h" 
#include "../../SDTAIController.h"
#include "../../SDTUtils.h"

EBTNodeResult::Type UMyBTTask_IsPlayerPoweredUp::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    ASDTAIController* AIController = Cast<ASDTAIController>(OwnerComp.GetAIOwner());
    if (!AIController)
        return EBTNodeResult::Failed;

    return AIController->IsPlayerInteractionBehaviorFlee() ? EBTNodeResult::Succeeded : EBTNodeResult::Failed;
}
