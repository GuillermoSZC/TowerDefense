#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UMG/Public/Components/Button.h"
#include "Engine/DataTable.h"
#include <Layout/Margin.h>
#include "TDButton.generated.h"

class UTDRichTextBlock;

/**
 *
 */
UCLASS()
class TOWERDEFENSE_API UTDButton : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual bool Initialize() override;
    virtual void NativePreConstruct() override;
    virtual void NativeConstruct() override;

public:
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UButton* ownerButton;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDRichTextBlock* richText;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance|Button Settings|Visual", meta = (InlineEditConditionToggle))
        bool useCustomTextStyleData;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance|Button Settings|Visual", meta = (ToolTip = "Edits text style data.", EditCondition = "useCustomTextStyleData"))
        UDataTable* textStyleData;

    UPROPERTY(EditAnywhere, Category = "Appearance|Button Settings|Visual")
        FButtonStyle ButtonStyle;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance|Button Settings|Data", meta = (InlineEditConditionToggle))
        bool useButtonText;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance|Button Settings|Data", meta = (ToolTip = "Edits button text.", EditCondition = "useButtonText"))
        FText buttonText;

protected:


private:
    UPROPERTY()
        FMargin ownPadding;


public:
    UFUNCTION()
        void TDSetButtonStyle(FButtonStyle& _buttonStyle);

    UFUNCTION()
        void TDSetPadding(FMargin _padding);

    UFUNCTION()
        void TDSetText(FText _text);

    UFUNCTION()
        FText TDGetText() const;

    UFUNCTION()
        void TDSetFont(UDataTable* _font);

protected:


private:


};
