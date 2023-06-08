#pragma once

#include "CoreMinimal.h"
#include <Engine/DataTable.h>
#include <Layout/Margin.h>
#include "TDLevelSelectorButtons.generated.h"

class UTDResourceCard;
class ULevel;
class UWorld;
class UTDButtonMap;

USTRUCT(BlueprintType)
struct FTDLevelSelectorButtons : public FTableRowBase
{
    GENERATED_BODY()

        UPROPERTY(EditAnywhere, meta = (InlineEditConditionToggle))
        bool bCanModify;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FText buttonName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ToolTip = "Edits text style data."))
        UDataTable* fonts;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "bCanModify"))
        FButtonStyle buttonStyle;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        TSoftObjectPtr<UWorld> levelReference;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FMargin padding;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        TSubclassOf<UTDButtonMap> buttonClass;

    FTDLevelSelectorButtons()
    {
        bCanModify = false;

        padding.Bottom = 10;
        padding.Top = 10;
        padding.Left = 10;
        padding.Right = 10;
    }
};
