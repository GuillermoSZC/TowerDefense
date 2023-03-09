// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TDButton.generated.h"

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
        class UButton* ownerButton;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        class UTDText* textButton;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance|Row Settings|Visual", meta = (InlineEditConditionToggle))
        bool useCustomTextStyleData;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance|Row Settings|Visual", meta = (ToolTip = "Edits text style data.", EditCondition = "useCustomTextStyleData"))
        UDataTable* textStyleData;

     UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance|Row Settings|Visual", meta = (ToolTip = "Edits if background is shown."))
         bool showButtonBackground;

//     UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance|Row Settings|Visual", meta = (ToolTip = "Animation index when the button is selected.", ClampMin = 0))
//         int selectionAnimationIndex;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance|Row Settings|Data", meta = (InlineEditConditionToggle))
        bool useButtonText;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance|Row Settings|Data", meta = (ToolTip = "Edits button text.", EditCondition = "useButtonText"))
        FText buttonText;

//     UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance|Row Settings|Data", meta = (ToolTip = "Edits button index."))
//         int buttonIndex;

protected:


private:


public:


protected:


private:


};
