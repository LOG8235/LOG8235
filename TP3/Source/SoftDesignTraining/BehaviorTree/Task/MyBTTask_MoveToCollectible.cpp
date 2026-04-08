// Fill out your copyright notice in the Description page of Project Settings.

#include "MyBTTask_MoveToCollectible.h"
#include "../../SDTAIController.h"

EBTNodeResult::Type UMyBTTask_MoveToCollectible::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    ASDTAIController* AIController = Cast<ASDTAIController>(OwnerComp.GetAIOwner());
    if (!AIController)
        return EBTNodeResult::Failed;


    bool wasReached = AIController->m_ReachedTarget;
    AIController->MoveToRandomCollectible();


    if (AIController->m_ReachedTarget == wasReached && wasReached)
        return EBTNodeResult::Failed;

    return EBTNodeResult::InProgress;
}
void UMyBTTask_MoveToCollectible::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    ASDTAIController* AIController = Cast<ASDTAIController>(OwnerComp.GetAIOwner());
    if (!AIController)
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        return;
    }

    if (AIController->AtJumpSegment)
        return;

    if (AIController->m_ReachedTarget)
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}

EBTNodeResult::Type UMyBTTask_MoveToCollectible::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    ASDTAIController* AIController = Cast<ASDTAIController>(OwnerComp.GetAIOwner());
    if (AIController && !AIController->AtJumpSegment)
        AIController->AIStateInterrupted();

    return EBTNodeResult::Aborted;
} 