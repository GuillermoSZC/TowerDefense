// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TDTextWithImage.generated.h"

/**
 *
 */
UCLASS()
class TOWERDEFENSE_API UTDTextWithImage : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual bool Initialize() override;
    virtual void NativePreConstruct() override;
    virtual void NativeConstruct() override;

public:
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        class UTDText* elementText;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        class UImage* ownerImage;

    UPROPERTY(BlueprintReadWrite, EditAnywhere ,Category = "Appearance|Custom properties")
        class UTexture2D* customTexture = nullptr;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        class USizeBox* elementBox;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        class UHorizontalBox* settingBox;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance|Row Settings|Visual", meta = (InlineEditConditionToggle))
        bool useOverridenWidth;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance|Row Settings|Visual", meta = (ToolTip = "Overrides row width.", EditCondition = "useOverridenWidth", ClampMin = 150, ClampMax = 1920, UIMin = 150, UIMax = 1920))
        float overridenWidth;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance|Row Settings|Visual", meta = (InlineEditConditionToggle))
        bool useOverridenHeight;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance|Row Settings|Visual", meta = (ToolTip = "Overrides row height.", EditCondition = "useOverridenHeight", ClampMin = 50, ClampMax = 1080, UIMin = 50, UIMax = 1080))
        float overridenHeight;

protected:

private:
    UPROPERTY()
        FText customText;

    UPROPERTY()
        int32 quantity;

    UPROPERTY()
        int32 minWidth = 150;

    UPROPERTY()
        int32 minHeight = 50;

public:
    UFUNCTION(BlueprintCallable)
        void TDSetText(FText _text);

    UFUNCTION(BlueprintCallable)
        FText TDGetText();

    UFUNCTION(BlueprintCallable)
        void TDSetQuantity(int32 _value);

    UFUNCTION(BlueprintCallable)
        int32 TDGetQuantity();

    UFUNCTION(BlueprintCallable)
        void TDSetTexture(UTexture2D* _texture);

    UFUNCTION(BlueprintCallable)
        UTexture2D* TDGetTexture(UTexture2D* _texture);
        

protected:

private:


};
