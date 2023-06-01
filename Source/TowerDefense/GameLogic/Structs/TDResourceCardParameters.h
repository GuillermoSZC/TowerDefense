#pragma once

#include "CoreMinimal.h"
#include <Engine/DataTable.h>
#include "GameLogic/TDInventoryEnum.h"
#include "GameLogic/TDLootEnum.h"
#include "TDResourceCardParameters.generated.h"

class UTDResourceCard;


USTRUCT(BlueprintType)
struct FTDResourceCardParameters : public FTableRowBase
{
    GENERATED_BODY()

        UPROPERTY(EditAnywhere, BlueprintReadWrite)
        ETDInventoryEnum column;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        ELootItems resource;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        UTexture2D* image;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FLinearColor color;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FMargin padding;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        TSubclassOf<UTDResourceCard> resourceClass;

    FTDResourceCardParameters()
    {
        color = FLinearColor::White;

        padding.Bottom = 10;
        padding.Top = 10;
        padding.Left = 10;
        padding.Right = 10;
    }


};
