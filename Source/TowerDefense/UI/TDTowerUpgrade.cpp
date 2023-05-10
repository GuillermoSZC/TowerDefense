// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TDTowerUpgrade.h"
#include "Map/TDTower.h"
#include "GameLogic/TDElementComponent.h"
#include "GameLogic/ElementsEnum.h"
#include "Utilities/TDButton.h"
#include <GameplayEffect.h>
#include "AttributesSets/TDLevelAttributeSet.h"

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

    plasmaUpgrade->ownerButton->OnClicked.AddDynamic(this, &UTDTowerUpgrade::TDPlasmaUpgrade);
    fireUpgrade->ownerButton->OnClicked.AddDynamic(this, &UTDTowerUpgrade::TDFireUpgrade);
    iceUpgrade->ownerButton->OnClicked.AddDynamic(this, &UTDTowerUpgrade::TDIceUpgrade);
    levelUp->ownerButton->OnClicked.AddDynamic(this, &UTDTowerUpgrade::TDLevelUp);
    exit->ownerButton->OnClicked.AddDynamic(this, &UTDTowerUpgrade::TDCloseUI);
}

void UTDTowerUpgrade::TDSetOwner(ATDTower* _owner)
{
    owner = _owner;
}

ATDTower* UTDTowerUpgrade::TDGetOwner()
{
    return owner;
}

void UTDTowerUpgrade::TDPlasmaUpgrade()
{
    TDSetElement(EElements::Plasma);
}

void UTDTowerUpgrade::TDFireUpgrade()
{
    TDSetElement(EElements::Fire);
}

void UTDTowerUpgrade::TDIceUpgrade()
{
    TDSetElement(EElements::Freeze);
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
    owner->GetAbilitySystemComponent()->ApplyGameplayEffectToSelf(staticEffect, 1, FGameplayEffectContextHandle());
    staticEffect->ConditionalBeginDestroy();
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
        UTDElementComponent* temp = ITDInterface::Execute_TDGetElementComponent(owner);
        temp->TDSetSpawnedElement(_element);
    }
}