// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TDLogWidget.h"
#include "Utilities/TDLogCard.h"
#include "UMG/Public/Components/VerticalBoxSlot.h"
#include "GameLogic/TDGameMode.h"
#include "UMG/Public/Components/CanvasPanel.h"
#include "UMG/Public/Components/CanvasPanelSlot.h"



bool UTDLogWidget::Initialize()
{
    Super::Initialize();

    if (UTDGameData::TDGetGameMode())
    {
        UTDGameData::TDGetGameMode()->FLootDropDelegate.AddDynamic(this, &UTDLogWidget::TDAddLogItem);

        for (int i = 0; i <= 20; ++i)
        {
            UTDLogCard* cardRef = CreateWidget<UTDLogCard>(canvasPanelWidget, cardClass);
            disabledCard.Add(cardRef);
            
        }
    }

    return true;
}

void UTDLogWidget::NativePreConstruct()
{
    Super::NativePreConstruct();
}

void UTDLogWidget::NativeConstruct()
{
    Super::NativeConstruct();
}

void UTDLogWidget::TDAddLogItem(ELootItems _item, FGameplayTag _category, int32 amount)
{

    FTDItemStruct newItem = FTDItemStruct(_item, _category, amount);

    if (!ItemsHeap.IsEmpty())
    {
        ItemsHeap.Add(newItem);
        return;
    }

    ItemsHeap.Add(newItem);
    TDAddCardToUI();

}



void UTDLogWidget::TDAddCardToUI()
{
    UTDLogCard* cardRef = disabledCard[0];
    disabledCard.RemoveAt(0);
    UCanvasPanelSlot* canvasSlotRef = canvasPanelWidget->AddChildToCanvas(cardRef);

    for (UTDLogCard* iter : cardsArray)
    {
        iter->TDPlayVerticalAnimation();
    }

    cardsArray.Add(cardRef);


    cardRef->FEndWidgetAnimationFadeInDelegate.AddDynamic(this, &UTDLogWidget::TDOnEndFadeInAnimation);
    cardRef->FEndWidgetAnimationFadeOutDelegate.AddDynamic(this, &UTDLogWidget::TDOnEndFadeOutAnimation);
    cardRef->FStartWidgetAnimationFadeInDelegate.AddDynamic(this, &UTDLogWidget::TDOnStartFadeInAnimation);
    cardRef->FStartWidgetAnimationFadeOutDelegate.AddDynamic(this, &UTDLogWidget::TDOnStartFadeOutAnimation);


    FAnchors anchor = FAnchors(1.f,0.5f);
    canvasSlotRef->SetAnchors(anchor);
    canvasSlotRef->SetAlignment(FVector2D(1.f,0.5f));
    cardRef->SetRenderTranslation(FVector2D(0.f, 100.f));
    cardRef->TDPrepareCard(ItemsHeap[0]);
    cardRef->TDPlayFadeInAnimation();

}


void UTDLogWidget::TDOnEndFadeInAnimation(UTDLogCard* _card)
{
    ItemsHeap.RemoveAt(0);
    _card->FEndWidgetAnimationFadeInDelegate.Clear();


    if (!ItemsHeap.IsEmpty())
    {
        TDAddCardToUI();
    }

}

void UTDLogWidget::TDOnEndFadeOutAnimation(UTDLogCard* _card)
{

    _card->FEndWidgetAnimationFadeInDelegate.Clear();
    _card->FEndWidgetAnimationFadeOutDelegate.Clear();
    _card->FStartWidgetAnimationFadeInDelegate.Clear();
    _card->FStartWidgetAnimationFadeOutDelegate.Clear();


    _card->StopAllAnimations();
    canvasPanelWidget->RemoveChild(_card);
    cardsArray.Remove(_card);
    disabledCard.Add(_card);
}

void UTDLogWidget::TDOnStartFadeInAnimation(UTDLogCard* _card)
{
    _card->FStartWidgetAnimationFadeInDelegate.Clear();
}

void UTDLogWidget::TDOnStartFadeOutAnimation(UTDLogCard* _card)
{
    _card->FStartWidgetAnimationFadeOutDelegate.Clear();
}
