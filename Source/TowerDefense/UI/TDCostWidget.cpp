#include "UI/TDCostWidget.h"
#include "Components/TDWidgetShopComponent.h"
#include "Utilities/TDComposedButton.h"
#include "GameLogic/TDBuyStruct.h"
#include "Interfaces/TDCostInterface.h"
#include "Utilities/TDTextWithImage.h"
#include "GameLogic/TDGameData.h"
#include "Character/TDPlayerCharacter.h"


bool UTDCostWidget::Initialize()
{
    Super::Initialize();

    return true;
}

void UTDCostWidget::NativePreConstruct()
{
    Super::NativePreConstruct();


}

void UTDCostWidget::NativeConstruct()
{
    Super::NativeConstruct();


    OnVisibilityChanged.AddDynamic(this, &UTDCostWidget::TDOnVisibilityChange);
    FUICostUpdateDelegate.AddDynamic(this, &UTDCostWidget::TDUpdateCost);
        
}

UTDWidgetShopComponent* UTDCostWidget::TDGetOwner()
{
    return owner;
}

void UTDCostWidget::TDSetOwner(UTDWidgetShopComponent* _owner)
{
    owner = _owner;
}

void UTDCostWidget::TDOnVisibilityChange(ESlateVisibility _visible)
{

}

void UTDCostWidget::TDUpdateCost()
{

}

void UTDCostWidget::TDUpdateGemCost(UTDComposedButton* _button, ELootItems _item)
{
    FBuyCost cost = FBuyCost();
    bool canAfford = false; 
    ITDCostInterface::Execute_TDCalculateElementChangeCost(owner->GetOwner(), cost, _item);
    _button->gems->TDSetText(UTDGameData::TDConvertIntToFText(cost.GemCost));
    canAfford = ITDCostInterface::Execute_TDCanAffordCostWithLoot(owner->GetOwner(), cost);
    _button->TDCanAfford(canAfford);
}

void UTDCostWidget::TDUpdateBPCostWithItem(UTDComposedButton* _button, ELootItems _item)
{
    FBuyCost cost = FBuyCost();
    bool canAfford = false;

    ITDCostInterface::Execute_TDCalcultateCostWithLoot(owner->GetOwner(), cost, _item);
    _button->scrap->TDSetText(UTDGameData::TDConvertIntToFText(cost.scrapCost));
    _button->bps->TDSetText(UTDGameData::TDConvertIntToFText(cost.BPCost));
    canAfford = ITDCostInterface::Execute_TDCanAffordCostWithLoot(owner->GetOwner(), cost);
    _button->TDCanAfford(canAfford);
}

FText UTDCostWidget::TDGetTextFromItem(ELootItems _item)
{
    ATDPlayerCharacter* playerRef = UTDGameData::TDGetPlayerRef();
    int32 inttemp = playerRef->TDGetAmountItemByItem(_item);
    FString StringTemp = FString::FromInt(inttemp);
    FText textTemp = FText::FromString(StringTemp);

    return textTemp;
}

void UTDCostWidget::TDUpdateInventoryToText(UTDTextWithImage* _text, ELootItems _item)
{
    _text->TDSetText(TDGetTextFromItem(_item));
}
