#include "BTService_UpdateChase.h"
#include "../../SDTAIController.h" 

UBTService_UpdateChase::UBTService_UpdateChase()
{
    NodeName = "Update Chase Position";
    Interval = 0.1f;
    RandomDeviation = 0.05f;
}

void UBTService_UpdateChase::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    ASDTAIController* AIController = Cast<ASDTAIController>(OwnerComp.GetAIOwner());
    if (AIController)
    {
        UE_LOG(LogTemp, Log, TEXT("UBTService_UpdateChase: AIController found calling MoveToEncirclementPosition()"));
        AIController->MoveToEncirclementPosition();
    }
}