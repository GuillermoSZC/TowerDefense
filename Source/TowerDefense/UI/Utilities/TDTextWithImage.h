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
    UPROPERTY(BlueprintReadWrite)
        class UTDText* textElement;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        class UImage* ownerImage;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        class USizeBox* elementBox;


protected:

private:
    UPROPERTY()
        FText customText;

    UPROPERTY()
        int32 quantity;

public:
    UFUNCTION(BlueprintCallable)
        void TDSetText(FText _text);

    UFUNCTION(BlueprintCallable)
        FText TDGetText();

    UFUNCTION(BlueprintCallable)
        void TDSetQuantity(int32 _value);

    UFUNCTION(BlueprintCallable)
        int32 TDGetQuantity();

protected:

private:


};
