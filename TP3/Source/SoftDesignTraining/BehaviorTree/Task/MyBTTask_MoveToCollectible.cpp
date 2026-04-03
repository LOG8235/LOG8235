// Fill out your copyright notice in the Description page of Project Settings.

#include "MyBTTask_MoveToCollectible.h"
#include "../../SDTAIController.h"

EBTNodeResult::Type UMyBTTask_MoveToCollectible::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    ASDTAIController* AIController = Cast<ASDTAIController>(OwnerComp.GetAIOwner());
    if (!AIController)
        return EBTNodeResult::Failed;

    AIController->MoveToRandomCollectible();
    return EBTNodeResult::Succeeded;
}
