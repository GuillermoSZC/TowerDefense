#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "TDEnemyStats.h"
#include "TDAbilitiesDataAsset.h"
#include "TDweaponDataAsset.h"
#include "TDEnemiesDataTable.generated.h"

/**
 *
 */
USTRUCT(BlueprintType)
struct TOWERDEFENSE_API FTDEnemiesDataTable : public FTableRowBase
{
    GENERATED_USTRUCT_BODY()

public:
    FTDEnemiesDataTable();
    ~FTDEnemiesDataTable();

public:
#pragma region ENEMY_MESH
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Mesh")
        TSoftObjectPtr<USkeletalMesh> enemyMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Mesh")
        FVector MeshPosition = FVector::ZeroVector;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Mesh")
        FVector MeshScale = FVector(1.f);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Mesh")
        UMaterialInterface* material;

#pragma endregion

#pragma region HUD
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
        FVector2D HealthBarSize = FVector2D(1.2f, 0.4f);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
        FVector HealthBarPosition = FVector(0.f, -40.f, 160.f);
#pragma endregion

#pragma region CAPSULE_VALUES
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Capsule Values")
        float capsuleHeight = 130.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Capsule Values")
        float capsuleRadius = 55.f;
#pragma endregion

#pragma region ANIMATION
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
        TSubclassOf<UAnimInstance> animationBlueprint;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
        TSoftObjectPtr<class UAnimMontage> animationMontaje;
#pragma endregion

#pragma region ROUND_VALUES
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Round Values")
        int32 weight;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Round Values")
        int32 firstPossibleApperance;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Round Values")
        int32 limitEnemiesPerRound;
#pragma endregion

#pragma region GAS_VALUES
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay Ability System Values")

        UTDEnemyStats* EnemyStatsDataAsset;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay Ability System Values")
        float movementVariation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay Ability System Values")
        UTDAbilitiesDataAsset* abiliyAsset;


    UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Gameplay Ability System Values")
        UTDweaponDataAsset* WeaponAsset;

#pragma endregion

#pragma region AI
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
        TSoftObjectPtr<class UBehaviorTree> behaviorTree;
#pragma endregion

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")
    FString DebugName;

};
