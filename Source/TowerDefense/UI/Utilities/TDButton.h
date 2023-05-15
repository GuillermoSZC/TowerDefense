// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UMG/Public/Components/Button.h"
#include "Engine/DataTable.h"
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

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance|Button Settings|Data", meta = (InlineEditConditionToggle))
        bool useButtonText;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance|Button Settings|Data", meta = (ToolTip = "Edits button text.", EditCondition = "useButtonText"))
        FText buttonText;


protected:


private:


public:


protected:


private:


};
