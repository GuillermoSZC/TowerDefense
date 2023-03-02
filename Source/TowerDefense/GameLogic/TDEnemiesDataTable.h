#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
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
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        TSoftObjectPtr<USkeletalMesh> enemyMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FVector MeshPosition = FVector::ZeroVector;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FVector MeshScale = FVector(1.f);

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float capsuleHeight = 130.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float capsuleRadius = 55.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        TSubclassOf<UAnimInstance> animationBlueprint;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        TSoftObjectPtr<class UAnimMontage> animationMontaje;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        int32 weight;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        int32 firstPossibleApperance;


    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        UDataTable* gasDataTable;

    UPROPERTY(EditAnywhere,BlueprintReadWrite)
    float movementVariation;


    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        TArray<TSubclassOf<class UGameplayAbility>> abiliyList;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        TSoftObjectPtr<class UBehaviorTree> behaviorTree;


        

protected:


private:


public:


protected:


private:


};
