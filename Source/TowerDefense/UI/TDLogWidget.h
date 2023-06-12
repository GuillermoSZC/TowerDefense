// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/TDUserWidget.h"
#include "TDLogWidget.generated.h"

class UTDLogCard;

/**
 *
 */
UCLASS()
class TOWERDEFENSE_API UTDLogWidget : public UTDUserWidget
{
    GENERATED_BODY()

public:


    virtual bool Initialize() override;
    virtual void NativePreConstruct() override;
    virtual void NativeConstruct() override;


public:


    UPROPERTY(EditAnywhere)
        TSubclassOf<UTDLogCard> cardClass;

    TArray<UTDLogCard*> cardsArray;


    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        class UCanvasPanel* canvasPanelWidget;

    
      

protected:

    UPROPERTY()
        TArray<ELootItems> ItemsHeap;

private:




public:

    UFUNCTION()
        void TDAddLogItem(ELootItems _item, int32 amount);

    UFUNCTION()
        void TDOnEndFadeInAnimation(UTDLogCard* _card);
    UFUNCTION()
        void TDOnEndFadeOutAnimation(UTDLogCard* _card);

    UFUNCTION()
        void TDOnStartFadeInAnimation(UTDLogCard* _card);
    UFUNCTION()
        void TDOnStartFadeOutAnimation(UTDLogCard* _card);

protected:

private:

    UFUNCTION()
        void TDAddCardToUI();

};
