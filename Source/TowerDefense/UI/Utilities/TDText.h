// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TDText.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UTDText : public UUserWidget
{
	GENERATED_BODY()

public:
    virtual bool Initialize() override;
    virtual void NativePreConstruct() override;
    virtual void NativeConstruct() override;


public:
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        class URichTextBlock* customRichText;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance|Custom properties", meta = (InlineEditConditionToggle))
        bool useCustomText;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance|Custom properties", meta = (ToolTip = "Edits custom text.", EditCondition = "useCustomText"))
        FText customText;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance|Custom properties", meta = (InlineEditConditionToggle))
        bool useCustomTextStyleData;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance|Custom properties", meta = (ToolTip = "Edits text style data.", EditCondition = "useCustomTextStyleData"))
        class UDataTable* textStyleData;

protected:


private:


public:
    UFUNCTION(BlueprintCallable)
        void TDSetCustomText(FText _newText);

    UFUNCTION(BlueprintCallable)
        void TDSetCustomTextStyle(UDataTable* _newTextStyleData);

protected:


private:


};
