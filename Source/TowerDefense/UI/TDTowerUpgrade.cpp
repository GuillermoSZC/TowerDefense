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

    TowersIcons.Add(ELootItems::BalisticBP, nullptr);
    TowersIcons.Add(ELootItems::SonicBP, nullptr);
    TowersIcons.Add(ELootItems::DeathRayBP, nullptr);
    TowersIcons.Add(ELootItems::SpeedTowerBP, nullptr);
    TowersIcons.Add(ELootItems::AttackTowerBP, nullptr);

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

   
    TDUpdateBPCostWithItem(levelUp);
    TDUpdateGemCost(fireUpgrade, ELootItems::Fire);
    TDUpdateGemCost(iceUpgrade, ELootItems::Ice);
    TDUpdateGemCost(plasmaUpgrade, ELootItems::Plasma);

    TDUpdateTowerBP(blueprint);
    TDUpdateInventoryToText(scrap, ELootItems::Scrap);
    TDUpdateInventoryToText(fire, ELootItems::Fire);
    TDUpdateInventoryToText(plasma, ELootItems::Plasma);
    TDUpdateInventoryToText(ice, ELootItems::Ice);

}

void UTDTowerUpgrade::TDOnVisibilityChange(ESlateVisibility _visible)
{

    if (_visible == ESlateVisibility::Visible)
    {
        towerOwner = owner->GetOwner<ATDTower>();
        FUICostUpdateDelegate.Broadcast();        
    }
}


void UTDTowerUpgrade::TDUpdateTowerBP(UTDTextWithImage* _text)
{
    _text->TDSetTexture(TowersIcons[towerOwner->TDGetItemToUpgrade()]);
    TDUpdateInventoryToText(_text, towerOwner->TDGetItemToUpgrade());

}

void UTDTowerUpgrade::TDPlasmaUpgrade()
{

    if (ITDCostInterface::Execute_TDCommitBuyUpgrade(owner->GetOwner(), ELootItems::Plasma))
    {
        TDBuyElement(EElements::Plasma);
        FUICostUpdateDelegate.Broadcast();
    }


}

void UTDTowerUpgrade::TDFireUpgrade()
{
    if (ITDCostInterface::Execute_TDCommitBuyUpgrade(owner->GetOwner(), ELootItems::Fire))
    {
        TDBuyElement(EElements::Fire);
        FUICostUpdateDelegate.Broadcast();
    }
}

void UTDTowerUpgrade::TDIceUpgrade()
{
    if (ITDCostInterface::Execute_TDCommitBuyUpgrade(owner->GetOwner(), ELootItems::Ice))
    {

        TDBuyElement(EElements::Freeze);
        FUICostUpdateDelegate.Broadcast();
    }


}

void UTDTowerUpgrade::TDLevelUp()
{

    if (ITDCostInterface::Execute_TDCommitBuyUpgrade(owner->GetOwner(), ELootItems::None))
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


   

}

void UTDTowerUpgrade::TDCloseUI()
{
    if (owner)
    {
        owner->TDHideUI();
    }
}

void UTDTowerUpgrade::TDBuyElement(EElements _element)
{
    if (owner)
    {
        UTDElementComponent* temp = ITDInterface::Execute_TDGetElementComponent(owner->GetOwner());
        temp->TDSetSpawnedElement(_element);        
    }
}