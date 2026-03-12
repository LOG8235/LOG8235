// Fill out your copyright notice in the Description page of Project Settings.

#include "SDTPathFollowingComponent.h"
#include "SoftDesignTraining.h"
#include "SDTUtils.h"
#include "SDTAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "NavigationSystem.h"
#include "NavLinkCustomInterface.h"
#include "DrawDebugHelpers.h"

USDTPathFollowingComponent::USDTPathFollowingComponent(const FObjectInitializer& ObjectInitializer)
{

}

/**
* This function is called every frame while the AI is following a path.
* MoveSegmentStartIndex and MoveSegmentEndIndex specify where we are on the path point array.
*/
void USDTPathFollowingComponent::FollowPathSegment(float DeltaTime)
{
    const TArray<FNavPathPoint>& points = Path->GetPathPoints();
    const FNavPathPoint& segmentStart = points[MoveSegmentStartIndex];
    const FNavPathPoint& segmentEnd = points[MoveSegmentEndIndex];


    if (SDTUtils::HasJumpFlag(segmentStart))
    {
        // Update jump along path / nav link proxy
        AController* MyController = Cast<AController>(GetOwner());

        if (MyController)
        {
            APawn* MyPawn = MyController->GetPawn();

            if (MyPawn)
            {
               
                FVector CurrentLoc = MyPawn->GetActorLocation();
				FVector End = segmentEnd.Location;

                float JumpSpeed = 1000.f; 
                FVector NewLoc = FMath::VInterpConstantTo(CurrentLoc, End, DeltaTime, JumpSpeed);

                jumProgress = FVector::Dist(JumpStartLocation, NewLoc) / FVector::Dist(JumpStartLocation, End);

                float ArcVisual = FMath::Sin(jumProgress * PI);
                float MaxHeight = 500.f;

                float BaseZ = FMath::Lerp(JumpStartLocation.Z, End.Z, jumProgress);
                NewLoc.Z = BaseZ + (ArcVisual * MaxHeight);

                MyPawn->SetActorLocation(NewLoc);

				if (jumProgress >= 0.95f)
                {
                    SetMoveSegment(MoveSegmentEndIndex);
                }

			}
        }
    }
    else
    {
        AController* MyController = Cast<AController>(GetOwner());

        if (MyController)
        {
            APawn* MyPawn = MyController->GetPawn();

            if (MyPawn)
            {

                FVector TargetLocation = points[MoveSegmentEndIndex].Location;
                FVector CurrentLocation = MyPawn->GetActorLocation();
                FVector Direction = (TargetLocation - CurrentLocation).GetSafeNormal2D();

                MyPawn->AddMovementInput(Direction, 1.0f);
                
            }
        }
    }
}

/**
* This function is called every time the AI has reached a new point on the path.
* If you need to do something at a given point in the path, this is the place.
*/
void USDTPathFollowingComponent::SetMoveSegment(int32 segmentStartIndex)
{
    Super::SetMoveSegment(segmentStartIndex);

    const TArray<FNavPathPoint>& points = Path->GetPathPoints();

    const FNavPathPoint& segmentStart = points[MoveSegmentStartIndex];

    uint16 RawFlags = FNavMeshNodeFlags(segmentStart.Flags).AreaFlags;

    if (SDTUtils::HasJumpFlag(segmentStart) && FNavMeshNodeFlags(segmentStart.Flags).IsNavLink())
    {

        isJumping = true;

        AController* MyController = Cast<AController>(GetOwner());
        ACharacter* MyChar = Cast<ACharacter>(MyController->GetPawn());

        if (MyChar && MyChar->GetCharacterMovement()) {
		    JumpStartLocation = MyChar->GetActorLocation();
            MyChar->GetCharacterMovement()->ClearAccumulatedForces();
            MyChar->GetCharacterMovement()->Velocity *= 0.05f;
            MyChar->GetCharacterMovement()->SetMovementMode(MOVE_Flying);
        }
        
    }
    else
    {
        isJumping = false;

        if (UCharacterMovementComponent* CharMovement = Cast<UCharacterMovementComponent>(MovementComp))
        {
            CharMovement->SetMovementMode(MOVE_Walking);
        }
        // Handle normal segments
    }
}

