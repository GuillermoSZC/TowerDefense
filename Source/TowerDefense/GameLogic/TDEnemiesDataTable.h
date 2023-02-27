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
        TAssetPtr<USkeletalMesh> enemyMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        TSubclassOf<UAnimInstance> animationBlueprint;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        int32 weight;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        UDataTable* gasDataTable;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        TArray<TSubclassOf<class UGameplayAbility>> abiliyList;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        TAssetPtr<class UBehaviorTree> behaviorTree;
        

protected:


private:


public:


protected:


private:


};
