// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SDTBaseAIController.h"
#include "SDTAIController.generated.h"
//#include "SDTChaseGroup.h"
class ASDTChaseGroup;

/**
 * 
 */
UCLASS(ClassGroup = AI, config = Game)
class SOFTDESIGNTRAINING_API ASDTAIController : public ASDTBaseAIController
{
	GENERATED_BODY()
public:
    enum PlayerInteractionBehavior
    {
        PlayerInteractionBehavior_Collect,
        PlayerInteractionBehavior_Chase,
        PlayerInteractionBehavior_Flee
    };

public:
    ASDTAIController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
    float m_DetectionCapsuleHalfLength = 500.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
    float m_DetectionCapsuleRadius = 250.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
    float m_DetectionCapsuleForwardStartingOffset = 100.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
    UCurveFloat* JumpCurve;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
    float JumpApexHeight = 300.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
    float JumpSpeed = 1.f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AI)
    bool AtJumpSegment = false;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AI)
    bool InAir = false;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AI)
    bool Landing = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
    UBehaviorTree* BehaviorTreeAsset;

    void MoveToRandomCollectible();
    void MoveToPlayer();
    void MoveToEncirclementPosition();
    void MoveToBestFleeLocation();
    void PlayerInteractionLoSUpdate();
    void OnPlayerInteractionNoLosDone();
    void OnMoveToTarget();
	void AIStateInterrupted();
	void OnGroupDissolved();						  
    virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;
    void RotateTowards(const FVector& targetLocation);
    void SetActorLocation(const FVector& targetLocation);
    bool IsPlayerInteractionBehaviorChase() const { return m_PlayerInteractionBehavior == PlayerInteractionBehavior_Chase; }
    bool IsPlayerInteractionBehaviorFlee() const { return m_PlayerInteractionBehavior == PlayerInteractionBehavior_Flee; }
    bool IsPlayerInteractionBehaviorCollect() const { return m_PlayerInteractionBehavior == PlayerInteractionBehavior_Collect; }
	PlayerInteractionBehavior m_PlayerInteractionBehavior;    
    virtual void UpdatePlayerInteraction(float deltaTime) override;
protected:
    float m_NextPerceptionUpdateTime = 0.f;
    float m_NextLoSUpdateTime = 0.f;
    float m_NextMoveRequestTime = 0.f;

    FVector m_LastRequestedMoveTarget = FVector::ZeroVector;
    bool m_HasRequestedMove = false;

    TWeakObjectPtr<ASDTChaseGroup> m_CachedChaseGroup;

    bool IsRelevantToPlayerView() const;
    bool ShouldIssueMoveRequest(const FVector& NewTarget, float Cooldown) const;
    void UpdateAITickRate();
    void RequestMoveIfNeeded(const FVector& Target, float AcceptanceRadius, float Cooldown, bool bUsePathfinding = true);


    void GetHightestPriorityDetectionHit(const TArray<FHitResult>& hits, FHitResult& outDetectionHit);
    void UpdatePlayerInteractionBehavior(const FHitResult& detectionHit, float deltaTime);
    PlayerInteractionBehavior GetCurrentPlayerInteractionBehavior(const FHitResult& hit);
    bool HasLoSOnHit(const FHitResult& hit);
    /** Rejoint ou quitte le groupe de poursuite selon le comportement courant. */
    void UpdateGroupMembership();

    FVector m_JumpTarget;
    FRotator m_ObstacleAvoidanceRotation;
    FTimerHandle m_PlayerInteractionNoLosTimer;


private:
    virtual void GoToBestTarget(float deltaTime) override;
    
	ASDTChaseGroup* GetOrCreateChaseGroup();
};
