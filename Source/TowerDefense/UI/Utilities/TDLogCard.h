// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameLogic/Structs/TDItemStrcut.h"
#include "TDLogCard.generated.h"

class UImage;
class UBorder;
class UTDText;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FActionWidgetAnimationSignature, UTDLogCard*, _card);


/**
 *
 */
UCLASS()
class TOWERDEFENSE_API UTDLogCard : public UUserWidget
{
    GENERATED_BODY()

public:



public:
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UImage* ownerImage;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UBorder* ownerBorder;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDText* ownerText;

    UPROPERTY(BlueprintReadOnly,VisibleAnywhere)
    FTDItemStruct itemStruct;

        UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite)
        FActionWidgetAnimationSignature FStartWidgetAnimationFadeInDelegate;

    UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite)
        FActionWidgetAnimationSignature FStartWidgetAnimationFadeOutDelegate;


    UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite)
        FActionWidgetAnimationSignature FEndWidgetAnimationFadeInDelegate;

    UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite)
        FActionWidgetAnimationSignature FEndWidgetAnimationFadeOutDelegate;



    UPROPERTY(EditAnywhere)
    TMap<ELootItems, UTexture2D*> ItemMapImage;

    UPROPERTY(EditAnywhere)
    TMap<FGameplayTag, FLinearColor> ColorBackgroundRarity;


protected:

private:


public:

    virtual bool Initialize() override;
    virtual void NativePreConstruct() override;
    virtual void NativeConstruct() override;


    UFUNCTION(BlueprintImplementableEvent)
        void TDPlayVerticalAnimation();


    UFUNCTION(BlueprintImplementableEvent)
        void TDPlayFadeInAnimation();


    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
        void TDPlayFadeOutAnimation();


    UFUNCTION()
    void TDPrepareCard(FTDItemStruct _item);
protected:

private:

};
