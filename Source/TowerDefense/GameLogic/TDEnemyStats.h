#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TDEnemyStats.generated.h"

class UDataTable;

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UTDEnemyStats : public UDataAsset
{
	GENERATED_BODY()

public:

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
        UDataTable* healthDataTable;

    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
        UDataTable* damageDataTable;

    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
        UDataTable* movementDataTable;
};
