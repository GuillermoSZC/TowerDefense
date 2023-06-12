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

void UTDLogWidget::TDAddLogItem(ELootItems _item, int32 amount)
{
    if (!ItemsHeap.IsEmpty())
    {
        ItemsHeap.Add(_item);
        return;
    }

    ItemsHeap.Add(_item);
    TDAddCardToUI();

}



void UTDLogWidget::TDAddCardToUI()
{
    UTDLogCard* cardRef = CreateWidget<UTDLogCard>(canvasPanelWidget, cardClass);
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
    _card->FEndWidgetAnimationFadeOutDelegate.Clear();

    canvasPanelWidget->RemoveChild(_card);
    cardsArray.Remove(_card);
    _card->ConditionalBeginDestroy();
}

void UTDLogWidget::TDOnStartFadeInAnimation(UTDLogCard* _card)
{

}

void UTDLogWidget::TDOnStartFadeOutAnimation(UTDLogCard* _card)
{

}
