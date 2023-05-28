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
        UTexture2D* image;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        int scrapCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        int bpCost;
};