// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTService_GetMReachedAndJump.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../../SDTBaseAIController.h"
#include "../../SDTAIController.h"

UMyBTService_GetMReachedAndJump::UMyBTService_GetMReachedAndJump()
{
    NodeName = TEXT("Set ReachedTarget/IsJumping From AIController");
    bNotifyTick = true;

    ReachedTargetKey.SelectedKeyName = TEXT("m_ReachedTarget");
    IsJumpingKey.SelectedKeyName = TEXT("IsJumping");
}

void UMyBTService_GetMReachedAndJump::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
    if (!Blackboard)
        return;

    ASDTBaseAIController* BaseAIController = Cast<ASDTBaseAIController>(OwnerComp.GetAIOwner());
    if (!BaseAIController)
        return;

    Blackboard->SetValueAsBool(ReachedTargetKey.SelectedKeyName, BaseAIController->m_ReachedTarget);

    bool bIsJumping = false;
    if (ASDTAIController* AIController = Cast<ASDTAIController>(BaseAIController))
    {
        bIsJumping = AIController->AtJumpSegment;
    }

    Blackboard->SetValueAsBool(IsJumpingKey.SelectedKeyName, bIsJumping);
}

