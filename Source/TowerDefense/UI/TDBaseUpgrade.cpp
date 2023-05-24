// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TDBaseUpgrade.h"
#include "Map/TDBase.h"
#include "GameLogic/TDGameData.h"
#include "AttributesSets/TDLevelAttributeSet.h"
#include "Components/TDWidgetShopComponent.h"
#include "Character/TDPlayerCharacter.h"
#include "GameLogic/TDElementComponent.h"
#include "Interfaces/TDInterface.h"
#include "Utilities/TDComposedButton.h"
#include "Utilities/TDBaseButton.h"
#include "Utilities/TDTextWithImage.h"


bool UTDBaseUpgrade::Initialize()
{
    Super::Initialize();

    return true;
}

void UTDBaseUpgrade::NativePreConstruct()
{
    Super::NativePreConstruct();


}

void UTDBaseUpgrade::NativeConstruct()
{
    Super::NativeConstruct();

    plasmaUpgrade->imgButton->OnClicked.AddDynamic(this, &UTDBaseUpgrade::TDPlasmaUpgrade);
    fireUpgrade->imgButton->OnClicked.AddDynamic(this, &UTDBaseUpgrade::TDFireUpgrade);
    iceUpgrade->imgButton->OnClicked.AddDynamic(this, &UTDBaseUpgrade::TDIceUpgrade);
    healthUpgrade->imgButton->OnClicked.AddDynamic(this, &UTDBaseUpgrade::TDHealthUpgrade);
    speedUpgrade->imgButton->OnClicked.AddDynamic(this, &UTDBaseUpgrade::TDSpeedUpgrade);
    damageUpgrade->imgButton->OnClicked.AddDynamic(this, &UTDBaseUpgrade::TDDamageUpgrade);
    exit->OnClicked.AddDynamic(this, &UTDBaseUpgrade::TDCloseUI);
}

void UTDBaseUpgrade::TDUpdateCost()
{
    FBuyCost cost = FBuyCost();

    ITDCostInterface::Execute_TDCalcultateCostWithLoot(owner->GetOwner(), cost, ELootItems::ArmorBP);
    healthUpgrade->scrap->TDSetText(UTDGameData::TDConvertIntToFText(cost.scrapCost));
    healthUpgrade->bps->TDSetText(UTDGameData::TDConvertIntToFText(cost.BPCost));

    ITDCostInterface::Execute_TDCalcultateCostWithLoot(owner->GetOwner(), cost, ELootItems::BootsBP);
    speedUpgrade->scrap->TDSetText(UTDGameData::TDConvertIntToFText(cost.scrapCost));
    speedUpgrade->bps->TDSetText(UTDGameData::TDConvertIntToFText(cost.BPCost));

    ITDCostInterface::Execute_TDCalcultateCostWithLoot(owner->GetOwner(), cost, ELootItems::SwordBP);
    damageUpgrade->scrap->TDSetText(UTDGameData::TDConvertIntToFText(cost.scrapCost));
    damageUpgrade->bps->TDSetText(UTDGameData::TDConvertIntToFText(cost.BPCost));

    ITDCostInterface::Execute_TDCalculateElementChangeCost(owner->GetOwner(), cost, EElements::Fire);
    fireUpgrade->gems->TDSetText(UTDGameData::TDConvertIntToFText(cost.GemCost));

    ITDCostInterface::Execute_TDCalculateElementChangeCost(owner->GetOwner(), cost, EElements::Plasma);
    plasmaUpgrade->gems->TDSetText(UTDGameData::TDConvertIntToFText(cost.GemCost));

    ITDCostInterface::Execute_TDCalculateElementChangeCost(owner->GetOwner(), cost, EElements::Freeze);
    iceUpgrade->gems->TDSetText(UTDGameData::TDConvertIntToFText(cost.GemCost));
}

void UTDBaseUpgrade::TDOnVisibilityChange(ESlateVisibility _visible)
{

    if (_visible == ESlateVisibility::Visible)
    {
        FUICostUpdateDelegate.Broadcast();
    }
}

void UTDBaseUpgrade::TDPlasmaUpgrade()
{
    TDSetElement(EElements::Plasma);
    FUICostUpdateDelegate.Broadcast();

   
}

void UTDBaseUpgrade::TDFireUpgrade()
{
    TDSetElement(EElements::Fire);
    FUICostUpdateDelegate.Broadcast();

}

void UTDBaseUpgrade::TDIceUpgrade()
{
    TDSetElement(EElements::Freeze);
    FUICostUpdateDelegate.Broadcast();

}

void UTDBaseUpgrade::TDHealthUpgrade()
{
    TDSetGameplayEffect(healthEffect);
    FUICostUpdateDelegate.Broadcast();

}

void UTDBaseUpgrade::TDSpeedUpgrade()
{
    TDSetGameplayEffect(speedEffect);
    FUICostUpdateDelegate.Broadcast();

}

void UTDBaseUpgrade::TDDamageUpgrade()
{
    TDSetGameplayEffect(damageEffect);
    FUICostUpdateDelegate.Broadcast();

}

void UTDBaseUpgrade::TDCloseUI()
{
    if (owner)
    {
        owner->TDHideUI();
    }    
}

void UTDBaseUpgrade::TDSetElement(EElements _element)
{

    UTDElementComponent* temp = ITDInterface::Execute_TDGetElementComponent(UTDGameData::TDGetPlayerRef());

    temp->TDSetSpawnedElement(_element);
}

// void UTDBaseUpgrade::TDLevelUp()
// {
//     UGameplayEffect* staticEffect = NewObject<UGameplayEffect>();
//     staticEffect->Modifiers.Empty();
//     FGameplayModifierInfo modif = FGameplayModifierInfo();
//     modif.ModifierOp = EGameplayModOp::Additive;
//     modif.Attribute = UTDLevelAttributeSet::GetlevelAttribute();
//     modif.ModifierMagnitude = FGameplayEffectModifierMagnitude(FScalableFloat(1));
//     staticEffect->Modifiers.Add(modif);
//     UTDGameData::TDGetPlayerRef()->abilitySystem->ApplyGameplayEffectToSelf(staticEffect, 1, FGameplayEffectContextHandle());
//     staticEffect->ConditionalBeginDestroy();
// }

void UTDBaseUpgrade::TDSetGameplayEffect(TSubclassOf<UGameplayEffect> _gameplayEffect)
{
    UGameplayEffect* staticEffect = Cast<UGameplayEffect>(_gameplayEffect->GetDefaultObject());
    UTDGameData::TDGetPlayerRef()->abilitySystem->ApplyGameplayEffectToSelf(staticEffect, 1, FGameplayEffectContextHandle());
    staticEffect->ConditionalBeginDestroy();
}