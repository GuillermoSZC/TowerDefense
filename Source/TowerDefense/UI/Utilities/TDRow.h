#pragma once

#include "CoreMinimal.h"
#include "UI/TDUserWidget.h"
#include "TDRow.generated.h"

class UTDRichTextBlock;
class USpacer;
class USizeBox;
class UBorder;

/**
    Row parent
 */
UCLASS()
class TOWERDEFENSE_API UTDRow : public UTDUserWidget
{
    GENERATED_BODY()
public:
    virtual bool Initialize() override;
    virtual void NativePreConstruct() override;
    virtual void NativeConstruct() override;

public:
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        USizeBox* rowBox;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance|Row Settings|Visual", meta = (InlineEditConditionToggle))
        bool useOverridenWidth;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance|Row Settings|Visual", meta = (ToolTip = "Overrides row width.", EditCondition = "useOverridenWidth", ClampMin = 500, ClampMax = 1920, UIMin = 500, UIMax = 1920))
        float overridenWidth;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDRichTextBlock* richText;

    UPROPERTY(EditAnywhere, Category = "Custom Properties")
        FText rowText;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UBorder* background;

protected:

private:

public:
    UFUNCTION()
        void TDSetText(FText _text);

protected:

private:

};
