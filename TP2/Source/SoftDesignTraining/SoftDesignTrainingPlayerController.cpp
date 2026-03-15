// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "SoftDesignTrainingPlayerController.h"
#include "SoftDesignTraining.h"
#include "SoftDesignTrainingMainCharacter.h"

#include "DrawDebugHelpers.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "SDTBridge.h"
#include "SDTBoatOperator.h"
#include "Engine/OverlapResult.h"
#include <NavigationSystem.h>
#include "NavigationPath.h"

ASoftDesignTrainingPlayerController::ASoftDesignTrainingPlayerController()
{
    // Make a path following component
    m_PathFollowingComponent = CreateDefaultSubobject<USDTPathFollowingComponent>(TEXT("PathFollowingComponent"));
    PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.bStartWithTickEnabled = true;

    m_ShowDebugPath = false;
}
void ASoftDesignTrainingPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Redessiner le chemin chaque frame si nécessaire
    if (m_ShowDebugPath)
    {
        ShowNavigationPath();
    }
}
void ASoftDesignTrainingPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    // Move camera
    InputComponent->BindAxis("MoveForward", this, &ASoftDesignTrainingPlayerController::MoveCameraForward);
    InputComponent->BindAxis("MoveRight", this, &ASoftDesignTrainingPlayerController::MoveCameraRight);

    // Zoom camera
    InputComponent->BindAxis("Zoom", this, &ASoftDesignTrainingPlayerController::ZoomCamera);

    // Move character on click
    InputComponent->BindAction("MoveCharacter", EInputEvent::IE_Released, this, &ASoftDesignTrainingPlayerController::MoveCharacter);
    
    InputComponent->BindAction("Activate", EInputEvent::IE_Pressed, this, &ASoftDesignTrainingPlayerController::Activate);
    InputComponent->BindAction("Activate", EInputEvent::IE_Released, this, &ASoftDesignTrainingPlayerController::Deactivate);
}

void ASoftDesignTrainingPlayerController::BeginPlay()
{
    Super::BeginPlay();

    // Always show the mouse
    bShowMouseCursor = true;

    // Allow character to be moved by default 
    m_CanMoveCharacter = true;

    // In case we are activating a bridge
    m_BridgeActivated = nullptr;

    // In case we are activating a boat operator
    m_BoatOperatorActivated = nullptr;
}

void ASoftDesignTrainingPlayerController::MoveCameraForward(float value)
{
    ASoftDesignTrainingMainCharacter* character = Cast<ASoftDesignTrainingMainCharacter>(GetPawn());

    if (character)
    {
        character->MoveCameraForward(value);
    }
}

void ASoftDesignTrainingPlayerController::MoveCameraRight(float value)
{
    ASoftDesignTrainingMainCharacter* character = Cast<ASoftDesignTrainingMainCharacter>(GetPawn());

    if (character)
    {
        character->MoveCameraRight(value);
    }
}

void ASoftDesignTrainingPlayerController::ZoomCamera(float axisValue)
{
    ASoftDesignTrainingMainCharacter* character = Cast<ASoftDesignTrainingMainCharacter>(GetPawn());

    if (character)
    {
        character->ZoomCamera(axisValue);
    }
}

void ASoftDesignTrainingPlayerController::MoveCharacter()
{
    // TODO : find the position of the mouse in the world 
    // And move the agent to this position IF possible
    // Validate you can move through m_CanMoveCharacter

    
    if (m_CanMoveCharacter && !m_PathFollowingComponent->isJumping)
    {
        FHitResult Hit;
        if (GetHitResultUnderCursor(ECC_Visibility, false, Hit))
        {
            UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, Hit.Location);
            m_ShowDebugPath = true;

       
        }
    }
    
}

void ASoftDesignTrainingPlayerController::ShowNavigationPath()
{
    if (m_PathFollowingComponent && m_PathFollowingComponent->HasValidPath())
    {
        const FNavPathSharedPtr path = m_PathFollowingComponent->GetPath();
        if (path.IsValid())
        {
            const TArray<FNavPathPoint>& pathPoints = path->GetPathPoints();

            for (int32 i = 0; i < pathPoints.Num(); ++i)
            {
                DrawDebugSphere(GetWorld(), pathPoints[i].Location, 25.f, 12, FColor::Blue, false, 0.05f);
                if (i < pathPoints.Num() - 1)
                {
                    DrawDebugLine(GetWorld(), pathPoints[i].Location, pathPoints[i + 1].Location, FColor::Cyan, false, 0.05f, 0, 5.f);
                }
            }
        }
    }
    else
    {
        m_ShowDebugPath = false;
    }
}

void ASoftDesignTrainingPlayerController::Activate()
{
    APawn* pawn = GetPawn();
    if (pawn == nullptr || m_PathFollowingComponent->isJumping)
    {
        return;
    }

    m_CanMoveCharacter = false;
    // TODO : Mouvement of the agent should be stopped !!
    StopMovement();
    m_ShowDebugPath = false;
    // Make an overlap to find what is near us to activate it
    TArray<FOverlapResult> results;
    GetWorld()->OverlapMultiByChannel(results, pawn->GetActorLocation(), pawn->GetActorRotation().Quaternion(), ECollisionChannel::ECC_WorldDynamic, FCollisionShape::MakeSphere(200.f));

    for (FOverlapResult& result : results)
    {
        AActor* actor = result.GetActor();
        ASDTBridge* bridge = Cast<ASDTBridge>(actor);
        if (bridge)
        {
            bridge->Activate();
            m_BridgeActivated = bridge;
            break;
        }

        ASDTBoatOperator* boatOperator = Cast<ASDTBoatOperator>(actor);
        if (boatOperator)
        {
            boatOperator->Activate();
            m_BoatOperatorActivated = boatOperator;
            break;
        }
    }
}

void ASoftDesignTrainingPlayerController::Deactivate()
{
    m_CanMoveCharacter = true;

    if (m_BridgeActivated)
    {
        m_BridgeActivated->Deactivate();
    }
    if (m_BoatOperatorActivated)
    {
        m_BoatOperatorActivated->Deactivate();
    }
}