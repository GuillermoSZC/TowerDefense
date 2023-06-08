#pragma once

#include "CoreMinimal.h"
#include <Engine/DataTable.h>
#include "TDLevelSelectorButtons.generated.h"

class UTDResourceCard;
class ULevel;
class UTDButton;


USTRUCT(BlueprintType)
struct FTDLevelSelectorButtons : public FTableRowBase
{
    GENERATED_BODY()

        UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FText buttonName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FSoftObjectPath levelReference;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FMargin padding;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        TSubclassOf<UTDButton> resourceClass;

    FTDLevelSelectorButtons()
    {
        padding.Bottom = 10;
        padding.Top = 10;
        padding.Left = 10;
        padding.Right = 10;
    }
};
