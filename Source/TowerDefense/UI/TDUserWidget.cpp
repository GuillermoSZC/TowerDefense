#include "UI/TDUserWidget.h"
#include "Components/TDWidgetShopComponent.h"
#include "Utilities/TDComposedButton.h"
#include "GameLogic/TDBuyStruct.h"
#include "Interfaces/TDCostInterface.h"
#include "Utilities/TDTextWithImage.h"
#include "GameLogic/TDGameData.h"


bool UTDUserWidget::Initialize()
{
    Super::Initialize();

    return false;
}

void UTDUserWidget::NativePreConstruct()
{
    Super::NativePreConstruct();


}

void UTDUserWidget::NativeConstruct()
{
    Super::NativeConstruct();


    OnVisibilityChanged.AddDynamic(this, &UTDUserWidget::TDOnVisibilityChange);
    FUICostUpdateDelegate.AddDynamic(this, &UTDUserWidget::TDUpdateCost);
        
}

UTDWidgetShopComponent* UTDUserWidget::TDGetOwner()
{
    return owner;
}

void UTDUserWidget::TDSetOwner(UTDWidgetShopComponent* _owner)
{
    owner = _owner;
}

void UTDUserWidget::TDOnVisibilityChange(ESlateVisibility _visible)
{

}

void UTDUserWidget::TDUpdateCost()
{

}

void UTDUserWidget::TDUpdateGemCost(UTDComposedButton* _button, ELootItems _item)
{
    FBuyCost cost = FBuyCost();
    bool canAfford = false; 
    ITDCostInterface::Execute_TDCalculateElementChangeCost(owner->GetOwner(), cost, _item);
    _button->gems->TDSetText(UTDGameData::TDConvertIntToFText(cost.GemCost));
    canAfford = ITDCostInterface::Execute_TDCanAffordCostWithLoot(owner->GetOwner(), cost);
    _button->TDCanAfford(canAfford);
}

// void UTDUserWidget::TDUpdateBPCost(UTDComposedButton* _button)
// {
//     FBuyCost cost = FBuyCost();
//     bool canAfford = false;
//     ITDCostInterface::Execute_TDCalcultateCost(owner->GetOwner(), cost);
//     _button->scrap->TDSetText(UTDGameData::TDConvertIntToFText(cost.scrapCost));
//     _button->bps->TDSetText(UTDGameData::TDConvertIntToFText(cost.BPCost));
//     canAfford = ITDCostInterface::Execute_TDCanAffordCost(owner->GetOwner(), cost);
//     _button->TDCanAfford(canAfford);
// }

void UTDUserWidget::TDUpdateBPCostWithItem(UTDComposedButton* _button, ELootItems _item)
{
    FBuyCost cost = FBuyCost();
    bool canAfford = false;

    ITDCostInterface::Execute_TDCalcultateCostWithLoot(owner->GetOwner(), cost, _item);
    _button->scrap->TDSetText(UTDGameData::TDConvertIntToFText(cost.scrapCost));
    _button->bps->TDSetText(UTDGameData::TDConvertIntToFText(cost.BPCost));
    canAfford = ITDCostInterface::Execute_TDCanAffordCostWithLoot(owner->GetOwner(), cost);
    _button->TDCanAfford(canAfford);
}
