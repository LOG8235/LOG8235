// LOG8235 - TP3 - Agents intelligents pour jeux vidéo
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SDTChaseGroup.generated.h"

class ASDTAIController;

/**
 * SDTChaseGroup - Gestionnaire du groupe de poursuite (Q2 + Q3)
 *
 * Un seul acteur de ce type existe dans le monde (pattern singleton via GetInstance).
 * Il maintient la liste des agents en train de poursuivre le joueur, partage la LKP
 * (Last Known Position) entre eux, et calcule les positions d'encerclement.
 *
 * Cycle de vie du groupe :
 *  - Un agent rejoint quand il passe en comportement Chase.
 *  - Le groupe est dissous (tous les agents retirés) quand :
 *      * le joueur meurt (téléportation au départ)
 *      * le joueur prend un power-up
 *      * tous les agents perdent la LKP simultanément
 */
UCLASS()
class SOFTDESIGNTRAINING_API ASDTChaseGroup : public AActor
{
    GENERATED_BODY()

public:
    ASDTChaseGroup();

    // --- Accès singleton ---
    // Retourne l'instance existante dans le monde, ou nullptr si absente.
    static ASDTChaseGroup* GetInstance(UWorld* World);

    // --- Gestion des membres ---

    /** Ajoute un agent au groupe. Sans effet s'il est déjà membre. */
    void AddMember(ASDTAIController* Controller);

    /** Retire un agent du groupe sans dissoudre les autres. */
    void RemoveMember(ASDTAIController* Controller);

    /** Dissout complètement le groupe (signale à tous les membres de repasser en Collect). */
    void DissolveGroup();

    bool IsMember(ASDTAIController* Controller) const;
    int32 GetMemberCount() const { return Members.Num(); }

    // --- LKP partagée (Last Known Position) ---

    /** Met à jour la LKP depuis un agent qui voit le joueur. */
    void UpdateLKP(const FVector& NewLKP);

    /** Retourne la dernière position connue du joueur. */
    FVector GetLKP() const { return LastKnownPlayerPosition; }

    bool HasValidLKP() const { return bHasValidLKP; }

    // --- Encerclement (Q3) ---

    /**
     * Calcule et assigne à chaque membre une position d'encerclement autour du joueur.
     * Utilise une distribution angulaire équitable autour de la LKP courante.
     * Appelé automatiquement à chaque UpdateLKP si le groupe a au moins 2 membres.
     */
    void RecalculateEncirclementPositions();

    /**
     * Retourne la position d'encerclement assignée à un controller donné.
     * Retourne la LKP elle-même si l'agent n'est pas dans le groupe.
     */
    FVector GetEncirclementPositionFor(ASDTAIController* Controller) const;

    // --- Debug ---
    virtual void Tick(float DeltaTime) override;

protected:
    virtual void BeginPlay() override;

private:
    // Liste des controllers membres du groupe
    UPROPERTY()
    TArray<ASDTAIController*> Members;

    // Position assignée à chaque membre pour l'encerclement
    TMap<ASDTAIController*, FVector> EncirclementPositions;

    // LKP partagée
    FVector LastKnownPlayerPosition;
    bool    bHasValidLKP = false;

    // Rayon autour du joueur pour les positions d'encerclement (en cm)
    UPROPERTY(EditAnywhere, Category = "Chase Group")
    float EncirclementRadius = 300.f;

    // Dessine les indicateurs de debug au-dessus des membres
    void DrawGroupDebug();

    // Optimise l'assignation agent→position pour minimiser la distance totale
    void OptimizePositionAssignment();

    FVector m_LastRequestedMoveTarget = FVector::ZeroVector;
};
