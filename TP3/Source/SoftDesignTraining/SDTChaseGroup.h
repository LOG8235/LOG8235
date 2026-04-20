
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SDTChaseGroup.generated.h"

class ASDTAIController;

UCLASS()
class SOFTDESIGNTRAINING_API ASDTChaseGroup : public AActor
{
    GENERATED_BODY()
    
public:
    ASDTChaseGroup();

    static ASDTChaseGroup* GetInstance(UWorld* World);

    void AddMember(ASDTAIController* Controller);

    void RemoveMember(ASDTAIController* Controller);

    void DissolveGroup();

    bool IsMember(ASDTAIController* Controller) const;
    int32 GetMemberCount() const { return Members.Num(); }

    void UpdateLKP(const FVector& NewLKP);

    FVector GetLKP() const { return LastKnownPlayerPosition; }

    bool HasValidLKP() const { return bHasValidLKP; }


    void RecalculateEncirclementPositions();

    FVector GetEncirclementPositionFor(ASDTAIController* Controller) const;

    FVector GetCloseEncirclementPositionFor(ASDTAIController* Controller) const;

    virtual void Tick(float DeltaTime) override;
    bool HasLkPTimeout() const { return LKPTimeout <= 0.f; };
protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY()
    TArray<ASDTAIController*> Members;

    TMap<ASDTAIController*, FVector> EncirclementPositions;

    FVector LastKnownPlayerPosition;
    bool    bHasValidLKP = false;
	float   LKPTimeout = 3.f;
    
    UPROPERTY(EditAnywhere, Category = "Chase Group")
    float EncirclementRadius = 500.f;

    void DrawGroupDebug();

    void OptimizePositionAssignment();
};
