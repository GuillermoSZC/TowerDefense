#pragma once

#include "CoreMinimal.h"
#include <Engine/DataTable.h>
#include "TDTowerComposedButtonParameters.generated.h"

class ATDTower;
class UTexture2D;

USTRUCT(BlueprintType)
struct FTDTowerComposedButtonParameters : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FText buttonTitle;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        TSubclassOf<ATDTower> tower;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        UTexture2D* image = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        int scrapCost = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        int bpCost = 0;
};