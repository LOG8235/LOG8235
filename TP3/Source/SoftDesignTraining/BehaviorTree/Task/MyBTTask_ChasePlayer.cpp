// Fill out your copyright notice in the Description page of Project Settings.

#include "MyBTTask_ChasePlayer.h"
#include "../../SDTAIController.h"

EBTNodeResult::Type UMyBTTask_ChasePlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    ASDTAIController* AIController = Cast<ASDTAIController>(OwnerComp.GetAIOwner());
    if (!AIController)
        return EBTNodeResult::Failed;

    AIController->MoveToEncirclementPosition(); 
    return EBTNodeResult::InProgress;
}

void UMyBTTask_ChasePlayer::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    ASDTAIController* AIController = Cast<ASDTAIController>(OwnerComp.GetAIOwner());
    if (!AIController)
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        return;
    }

    // Attend la fin du saut avant de verifier la completion
    if (AIController->AtJumpSegment)
        return;

    if (AIController->m_ReachedTarget)
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}
EBTNodeResult::Type UMyBTTask_ChasePlayer::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    ASDTAIController* AIController = Cast<ASDTAIController>(OwnerComp.GetAIOwner());
    if (AIController && !AIController->AtJumpSegment)
        AIController->AIStateInterrupted();

    return EBTNodeResult::Aborted;
}