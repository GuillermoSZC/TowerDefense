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



    UPROPERTY(EditAnywhere)
        TObjectPtr<USoundBase> Sound;



protected:


private:
    UPROPERTY()
        FMargin ownPadding;

#pragma region ANIM_PROPERTIES
    UPROPERTY()
        bool hasBeenAnimated = false;

    UPROPERTY()
        bool isActive = false;
#pragma endregion

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

#pragma region WIDGET_ANIMATIONS
    UFUNCTION(BlueprintPure)
        bool TDGetButtonAnimated() const;

    UFUNCTION(BlueprintCallable)
        void TDButtonAnimated(bool _value);

    UFUNCTION(BlueprintPure)
        bool TDGetIsActive() const;

    UFUNCTION(BlueprintCallable)
        void TDSetIsActive(bool _value);

    UFUNCTION(BlueprintNativeEvent)
        void TDClickedToRight();

    UFUNCTION(BlueprintNativeEvent)
        void TDUnselected();

#pragma endregion
protected:
    UFUNCTION(BlueprintImplementableEvent)
        void TDPlayButtonSound();

private:


};
