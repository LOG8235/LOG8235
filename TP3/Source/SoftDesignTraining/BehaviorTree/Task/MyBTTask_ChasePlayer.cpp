// Fill out your copyright notice in the Description page of Project Settings.

#include "MyBTTask_ChasePlayer.h"
#include "../../SDTAIController.h"

EBTNodeResult::Type UMyBTTask_ChasePlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    ASDTAIController* AIController = Cast<ASDTAIController>(OwnerComp.GetAIOwner());
    if (!AIController)
        return EBTNodeResult::Failed;

    AIController->MoveToPlayer();

    return EBTNodeResult::Succeeded;
}
