// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTService_GetMReachedAndJump.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../../SDTBaseAIController.h"
#include "../../SDTAIController.h"

UMyBTService_GetMReachedAndJump::UMyBTService_GetMReachedAndJump()
{
    NodeName = TEXT("Set ReachedTarget/IsJumping From AIController");
    bNotifyTick = true;
    // Tick a chaque frame pour des transitions reactives
    Interval = 0.0f;
    RandomDeviation = 0.0f;

    ReachedTargetKey.SelectedKeyName = TEXT("m_ReachedTarget");
    IsJumpingKey.SelectedKeyName = TEXT("IsJumping");
}

void UMyBTService_GetMReachedAndJump::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
    if (!Blackboard)
        return;

    ASDTAIController* AIController = Cast<ASDTAIController>(OwnerComp.GetAIOwner());
    if (!AIController)
        return;

    Blackboard->SetValueAsBool(ReachedTargetKey.SelectedKeyName, AIController->m_ReachedTarget);


    Blackboard->SetValueAsBool(IsJumpingKey.SelectedKeyName, AIController->AtJumpSegment);
    
    // Synchronise les nouvelles cles pour les decorateurs de condition
	Blackboard->SetValueAsBool(TEXT("IsChasing"), AIController->IsPlayerInteractionBehaviorChase());
	Blackboard->SetValueAsBool(TEXT("IsFleeing"), AIController->IsPlayerInteractionBehaviorFlee());
}

