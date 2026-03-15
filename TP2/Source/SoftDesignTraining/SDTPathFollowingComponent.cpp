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
    if (!Path.IsValid()) return;
    const TArray<FNavPathPoint>& points = Path->GetPathPoints();
    if (MoveSegmentStartIndex >= points.Num() || MoveSegmentEndIndex >= points.Num()) return;
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

                const float JumpDuration = 1.5f;
                jumProgress += DeltaTime / JumpDuration;
                jumProgress = FMath::Clamp(jumProgress, 0.f, 1.f);

                // Interpolation XY lineaire entre depart et arrivee
                FVector NewLocation = FMath::Lerp(JumpStartLocation, segmentEnd.Location, jumProgress);

                // Hauteur parabolique via JumpCurve si disponible, sinon arc manuel
                float HeightOffset = 0.f;
                if (JumpCurve)
                {
                    HeightOffset = JumpCurve->GetFloatValue(jumProgress);
                }
                else
                {
                    // Arc parabolique simple : sin(progress * PI) * hauteur max
                    HeightOffset = FMath::Sin(jumProgress * PI) * 300.f;
                }
                NewLocation.Z += HeightOffset;
                MyPawn->SetActorLocation(NewLocation, false, nullptr, ETeleportType::TeleportPhysics);

                // Orienter le pawn vers la destination pendant le saut
                FVector Direction = (segmentEnd.Location - JumpStartLocation).GetSafeNormal2D();
                if (!Direction.IsNearlyZero())
                {
                    MyPawn->SetActorRotation(Direction.Rotation());
                }

                // Saut termine
                if (jumProgress >= 0.98f && isJumping)
                {
                    isJumping = false;
                    jumProgress = 1.f;
                    ACharacter* MyChar = Cast<ACharacter>(MyPawn);
                    if (MyChar && MyChar->GetCharacterMovement())
                    {
                        MyChar->SetActorLocation(segmentEnd.Location, false, nullptr, ETeleportType::TeleportPhysics);

                        UCharacterMovementComponent* MoveComp = MyChar->GetCharacterMovement();
                        MoveComp->SetMovementMode(MOVE_Walking);
                        MoveComp->StopMovementImmediately();
                        MoveComp->Velocity = FVector::ZeroVector;
                        MoveComp->ClearAccumulatedForces();
                    }

                    OnSegmentFinished();
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
            jumProgress = 0.f;
            isJumping = true;
        }

    }
    else
    {
        isJumping = false;
        jumProgress = 0.f;

        if (UCharacterMovementComponent* CharMovement = Cast<UCharacterMovementComponent>(MovementComp))
        {
            CharMovement->SetMovementMode(MOVE_Walking);
        }
        // Handle normal segments
    }
}