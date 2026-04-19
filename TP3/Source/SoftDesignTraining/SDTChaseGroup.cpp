// LOG8235 - TP3 - Agents intelligents pour jeux vidéo
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

// ---------------------------------------------------------------------------
// Singleton
// ---------------------------------------------------------------------------

ASDTChaseGroup* ASDTChaseGroup::GetInstance(UWorld* World)
{
    if (!World)
        return nullptr;

    // Cherche un acteur existant de ce type dans le monde
    for (TActorIterator<ASDTChaseGroup> It(World); It; ++It)
        return *It;

    // Aucun trouvé : en crée un
    return World->SpawnActor<ASDTChaseGroup>();
}

// ---------------------------------------------------------------------------
// Gestion des membres
// ---------------------------------------------------------------------------

void ASDTChaseGroup::AddMember(ASDTAIController* Controller)
{
    if (!Controller || Members.Contains(Controller))
        return;

    Members.Add(Controller);

    // Recalcule les positions dès qu'un membre rejoint
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
    // Notifie chaque membre que le groupe est dissous :
    // l'agent doit repasser en Collect
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

// ---------------------------------------------------------------------------
// LKP partagée
// ---------------------------------------------------------------------------

void ASDTChaseGroup::UpdateLKP(const FVector& NewLKP)
{
    LastKnownPlayerPosition = NewLKP;
    bHasValidLKP = true;

    RecalculateEncirclementPositions();
}

// ---------------------------------------------------------------------------
// Calcul des positions d'encerclement (Q3)
// ---------------------------------------------------------------------------

void ASDTChaseGroup::RecalculateEncirclementPositions()
{
    if (Members.Num() == 0 || !bHasValidLKP)
        return;

    UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(GetWorld());
    const int32 Count = Members.Num();

    // Distribue les agents en éventail à 360° autour de la LKP.
    // Pour un seul agent, il va directement sur la LKP.
    for (int32 i = 0; i < Count; ++i)
    {
        ASDTAIController* Member = Members[i];
        if (!Member)
            continue;

        float AngleDeg = (360.f / Count) * i;
        float AngleRad = FMath::DegreesToRadians(AngleDeg);

        // Position idéale sur le cercle d'encerclement
        FVector IdealPos = LastKnownPlayerPosition
            + FVector(FMath::Cos(AngleRad), FMath::Sin(AngleRad), 0.f) * EncirclementRadius;

        // Projette sur le navmesh pour garantir une position atteignable
        FNavLocation NavPos;
        if (NavSys && NavSys->ProjectPointToNavigation(IdealPos, NavPos, FVector(200.f, 200.f, 200.f)))
        {
            EncirclementPositions.Add(Member, NavPos.Location);
        }
        else
        {
            // Fallback : utilise la LKP directement si la projection échoue
            EncirclementPositions.Add(Member, LastKnownPlayerPosition);
        }
    }

    // Optimise l'assignation : swapper les positions pour minimiser la distance totale
    // (algorithme glouton en O(n²), suffisant pour des groupes de taille Pac-Man)
    OptimizePositionAssignment();
}

void ASDTChaseGroup::OptimizePositionAssignment()
{
    // Collecte agents et positions dans des tableaux ordonnés
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

    // Assignation gloutonne : pour chaque agent, prend la position la plus proche
    // parmi celles non encore assignées
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
        int32 BestIdx = i; // fallback

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

    // Fallback : LKP directe si l'agent n'est pas dans la map
    return LastKnownPlayerPosition;
}

// ---------------------------------------------------------------------------
// Tick : debug + vérification de la LKP
// ---------------------------------------------------------------------------

void ASDTChaseGroup::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    DrawGroupDebug();

    // Vérifie si le joueur est powered up → dissout le groupe
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
    // Dessine un indicateur au-dessus de la tête de chaque membre (Q2)
    for (ASDTAIController* Member : Members)
    {
        if (!Member || !Member->GetPawn())
            continue;

        FVector HeadPos = Member->GetPawn()->GetActorLocation() + FVector(0.f, 0.f, 120.f);

        // Sphère rouge au-dessus de la tête
        DrawDebugSphere(GetWorld(), HeadPos, 20.f, 8, FColor::Red, false, -1.f, 0, 2.f);

        // Texte "CHASE GROUP"
        DrawDebugString(GetWorld(), HeadPos + FVector(0.f, 0.f, 25.f),
            TEXT("CHASE GROUP"), nullptr, FColor::Red, 0.f, false);
    }
}