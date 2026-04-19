#include "SDTChaseGroup.h"
#include "SDTAIController.h"
#include "SDTUtils.h"
#include "DrawDebugHelpers.h"
#include "EngineUtils.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "NavigationSystem.h"

ASDTChaseGroup::ASDTChaseGroup()
{
    PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.bStartWithTickEnabled = true;
}

void ASDTChaseGroup::BeginPlay()
{
    Super::BeginPlay();
}

ASDTChaseGroup* ASDTChaseGroup::GetInstance(UWorld* World)
{
    if (!World)
        return nullptr;

    for (TActorIterator<ASDTChaseGroup> It(World); It; ++It)
        return *It;

    return World->SpawnActor<ASDTChaseGroup>();
}

void ASDTChaseGroup::AddMember(ASDTAIController* Controller)
{
    if (!Controller || Members.Contains(Controller))
        return;

    Members.Add(Controller);

    if (bHasValidLKP)
        RecalculateEncirclementPositions();
}

void ASDTChaseGroup::RemoveMember(ASDTAIController* Controller)
{
    if (!Controller)
        return;

    Members.Remove(Controller);
    EncirclementPositions.Remove(Controller);

    if (bHasValidLKP && Members.Num() > 0)
        RecalculateEncirclementPositions();
}

void ASDTChaseGroup::DissolveGroup()
{

    for (ASDTAIController* Member : Members)
    {
        if (Member)
            Member->OnGroupDissolved();
    }

    Members.Empty();
    EncirclementPositions.Empty();
    bHasValidLKP = false;
}

bool ASDTChaseGroup::IsMember(ASDTAIController* Controller) const
{
    return Members.Contains(Controller);
}


void ASDTChaseGroup::UpdateLKP(const FVector& NewLKP)
{

    LastKnownPlayerPosition = NewLKP;
    bHasValidLKP = true;
	LKPTimeout = 3.f;
    RecalculateEncirclementPositions();
}


void ASDTChaseGroup::RecalculateEncirclementPositions()
{
    if (Members.Num() == 0 || !bHasValidLKP)
        return;

    UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(GetWorld());
    const int32 Count = Members.Num();

    for (int32 i = 0; i < Count; ++i)
    {
        ASDTAIController* Member = Members[i];
        if (!Member)
            continue;

        float AngleDeg = (360.f / Count) * i;
        float AngleRad = FMath::DegreesToRadians(AngleDeg);
        FVector IdealPos = LastKnownPlayerPosition
            + FVector(FMath::Cos(AngleRad), FMath::Sin(AngleRad), 0.f) * EncirclementRadius;
        FNavLocation NavPos;
        if (NavSys && NavSys->ProjectPointToNavigation(IdealPos, NavPos, FVector(200.f, 200.f, 200.f)))
        {
            EncirclementPositions.Add(Member, NavPos.Location);
        }
        else
        {
            EncirclementPositions.Add(Member, LastKnownPlayerPosition);
        }
    }
    OptimizePositionAssignment();
}

void ASDTChaseGroup::OptimizePositionAssignment()
{
    TArray<ASDTAIController*> AgentList;
    TArray<FVector> PosList;

    for (auto& Pair : EncirclementPositions)
    {
        if (Pair.Key)
        {
            AgentList.Add(Pair.Key);
            PosList.Add(Pair.Value);
        }
    }

    const int32 N = AgentList.Num();
    if (N < 2)
        return;

    TArray<bool> Assigned;
    Assigned.Init(false, N);
    TMap<ASDTAIController*, FVector> OptimalMap;

    for (int32 i = 0; i < N; ++i)
    {
        APawn* Pawn = AgentList[i]->GetPawn();
        if (!Pawn)
        {
            OptimalMap.Add(AgentList[i], PosList[i]);
            continue;
        }

        FVector AgentLoc = Pawn->GetActorLocation();
        float BestDist = FLT_MAX;
        int32 BestIdx = i;

        for (int32 j = 0; j < N; ++j)
        {
            if (Assigned[j])
                continue;

            float Dist = FVector::DistSquared(AgentLoc, PosList[j]);
            if (Dist < BestDist)
            {
                BestDist = Dist;
                BestIdx = j;
            }
        }

        Assigned[BestIdx] = true;
        OptimalMap.Add(AgentList[i], PosList[BestIdx]);
    }

    EncirclementPositions = OptimalMap;
}

FVector ASDTChaseGroup::GetEncirclementPositionFor(ASDTAIController* Controller) const
{
    if (const FVector* Pos = EncirclementPositions.Find(Controller))
        return *Pos;

    return LastKnownPlayerPosition;
}

void ASDTChaseGroup::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if (HasLkPTimeout()) {
		DissolveGroup();
		LKPTimeout = 3.f;
    }
	LKPTimeout -= DeltaTime;

    DrawGroupDebug();
    if (bHasValidLKP && Members.Num() > 0)
    {
        if (SDTUtils::IsPlayerPoweredUp(GetWorld()))
        {
            DissolveGroup();
        }
    }
}

void ASDTChaseGroup::DrawGroupDebug()
{
    for (ASDTAIController* Member : Members)
    {
        if (!Member || !Member->GetPawn())
            continue;

        FVector HeadPos = Member->GetPawn()->GetActorLocation() + FVector(0.f, 0.f, 120.f);

        DrawDebugSphere(GetWorld(), HeadPos, 20.f, 8, FColor::Red, false, -1.f, 0, 2.f);

        DrawDebugString(GetWorld(), HeadPos + FVector(0.f, 0.f, 25.f),
            TEXT("CHASE GROUP"), nullptr, FColor::Red, 0.f, false);
    }
}