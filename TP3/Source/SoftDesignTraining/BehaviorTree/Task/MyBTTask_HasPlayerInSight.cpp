// Fill out your copyright notice in the Description page of Project Settings.

#include "MyBTTask_HasPlayerInSight.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../../SDTAIController.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

EBTNodeResult::Type UMyBTTask_HasPlayerInSight::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    ASDTAIController* AIController = Cast<ASDTAIController>(OwnerComp.GetAIOwner());
    if (!AIController)
        return EBTNodeResult::Failed;

    return AIController->IsPlayerInteractionBehaviorChase() ? EBTNodeResult::Succeeded : EBTNodeResult::Failed;
}
