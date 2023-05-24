// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TDTowerUpgrade.h"
#include "Map/TDTower.h"
#include "GameLogic/TDElementComponent.h"
#include "GameLogic/ElementsEnum.h"
#include <GameplayEffect.h>
#include "AttributesSets/TDLevelAttributeSet.h"
#include "Components/TDWidgetShopComponent.h"
#include "Utilities/TDComposedButton.h"
#include "Utilities/TDBaseButton.h"


bool UTDTowerUpgrade::Initialize()
{
    Super::Initialize();

    return true;
}

void UTDTowerUpgrade::NativePreConstruct()
{
    Super::NativePreConstruct();


}

void UTDTowerUpgrade::NativeConstruct()
{
    Super::NativeConstruct();

    plasmaUpgrade->imgButton->OnClicked.AddDynamic(this, &UTDTowerUpgrade::TDPlasmaUpgrade);
    fireUpgrade->imgButton->OnClicked.AddDynamic(this, &UTDTowerUpgrade::TDFireUpgrade);
    iceUpgrade->imgButton->OnClicked.AddDynamic(this, &UTDTowerUpgrade::TDIceUpgrade);
    levelUp->imgButton->OnClicked.AddDynamic(this, &UTDTowerUpgrade::TDLevelUp);
    exit->OnClicked.AddDynamic(this, &UTDTowerUpgrade::TDCloseUI);
}

void UTDTowerUpgrade::TDUpdateCost()
{

    TDUpdateTowerLevelUpCost(levelUp);
    TDUpdateGemCost(fireUpgrade, EElements::Fire,ELootItems::Fire);
    TDUpdateGemCost(iceUpgrade, EElements::Freeze,ELootItems::Ice);
    TDUpdateGemCost(plasmaUpgrade, EElements::Plasma,ELootItems::Plasma);

}

void UTDTowerUpgrade::TDOnVisibilityChange(ESlateVisibility _visible)
{

    if (_visible == ESlateVisibility::Visible)
    {
        FUICostUpdateDelegate.Broadcast();        
    }
}

void UTDTowerUpgrade::TDUpdateGemCost(UTDComposedButton* _button, EElements _element, ELootItems _item)
{
    FBuyCost cost = FBuyCost();
    bool canAfford = false;
    ITDCostInterface::Execute_TDCalculateElementChangeCost(owner->GetOwner(), cost, _element);
    _button->gems->TDSetText(UTDGameData::TDConvertIntToFText(cost.GemCost));
    canAfford = ITDCostInterface::Execute_TDCanAffordElementChange(owner->GetOwner(), cost, _item);
    _button->TDCanAfford(canAfford);
}

void UTDTowerUpgrade::TDUpdateTowerLevelUpCost(UTDComposedButton* _button)
{
    FBuyCost cost = FBuyCost();
    bool canAfford = false;
    ITDCostInterface::Execute_TDCalcultateCost(owner->GetOwner(), cost);
    _button->scrap->TDSetText(UTDGameData::TDConvertIntToFText(cost.scrapCost));
    _button->bps->TDSetText(UTDGameData::TDConvertIntToFText(cost.BPCost));
    canAfford = ITDCostInterface::Execute_TDCanAffordCost(owner->GetOwner(), cost);
    levelUp->TDCanAfford(canAfford);
}

void UTDTowerUpgrade::TDPlasmaUpgrade()
{
    TDSetElement(EElements::Plasma);
    FUICostUpdateDelegate.Broadcast();

}

void UTDTowerUpgrade::TDFireUpgrade()
{
    TDSetElement(EElements::Fire);
    FUICostUpdateDelegate.Broadcast();

}

void UTDTowerUpgrade::TDIceUpgrade()
{
    TDSetElement(EElements::Freeze);
    FUICostUpdateDelegate.Broadcast();

}

void UTDTowerUpgrade::TDLevelUp()
{
    UGameplayEffect* staticEffect = NewObject<UGameplayEffect>();
    staticEffect->Modifiers.Empty();
    FGameplayModifierInfo modif = FGameplayModifierInfo();
    modif.ModifierOp = EGameplayModOp::Additive;
    modif.Attribute = UTDLevelAttributeSet::GetlevelAttribute();
    modif.ModifierMagnitude = FGameplayEffectModifierMagnitude(FScalableFloat(1));
    staticEffect->Modifiers.Add(modif);
    Cast<ATDTower>(owner->GetOwner())->GetAbilitySystemComponent()->ApplyGameplayEffectToSelf(staticEffect, 1, FGameplayEffectContextHandle());
    staticEffect->ConditionalBeginDestroy();

    FUICostUpdateDelegate.Broadcast();

}

void UTDTowerUpgrade::TDCloseUI()
{
    if (owner)
    {
        owner->TDHideUI();
    }
}

void UTDTowerUpgrade::TDSetElement(EElements _element)
{
    if (owner)
    {
        UTDElementComponent* temp = ITDInterface::Execute_TDGetElementComponent(owner->GetOwner());
        temp->TDSetSpawnedElement(_element);        
    }
}