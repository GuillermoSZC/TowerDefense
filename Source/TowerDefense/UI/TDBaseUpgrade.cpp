// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TDBaseUpgrade.h"
#include "Utilities/TDButton.h"
#include "Map/TDBase.h"
#include "GameLogic/TDGameData.h"
#include "AttributesSets/TDLevelAttributeSet.h"
#include "Components/TDWidgetShopComponent.h"
#include "Character/TDPlayerCharacter.h"
#include "GameLogic/TDElementComponent.h"
#include "Interfaces/TDInterface.h"

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

    plasmaUpgrade->ownerButton->OnClicked.AddDynamic(this, &UTDBaseUpgrade::TDPlasmaUpgrade);
    fireUpgrade->ownerButton->OnClicked.AddDynamic(this, &UTDBaseUpgrade::TDFireUpgrade);
    iceUpgrade->ownerButton->OnClicked.AddDynamic(this, &UTDBaseUpgrade::TDIceUpgrade);
    healthUpgrade->ownerButton->OnClicked.AddDynamic(this, &UTDBaseUpgrade::TDHealthUpgrade);
    speedUpgrade->ownerButton->OnClicked.AddDynamic(this, &UTDBaseUpgrade::TDSpeedUpgrade);
    damageUpgrade->ownerButton->OnClicked.AddDynamic(this, &UTDBaseUpgrade::TDDamageUpgrade);
    exit->ownerButton->OnClicked.AddDynamic(this, &UTDBaseUpgrade::TDCloseUI);
}

void UTDBaseUpgrade::TDPlasmaUpgrade()
{
    TDSetElement(EElements::Plasma);
    TDLevelUp();
}

void UTDBaseUpgrade::TDFireUpgrade()
{
    TDSetElement(EElements::Fire);
    TDLevelUp();
}

void UTDBaseUpgrade::TDIceUpgrade()
{
    TDSetElement(EElements::Freeze);
    TDLevelUp();
}

void UTDBaseUpgrade::TDHealthUpgrade()
{
    TDSetGameplayEffect(healthEffect);
}

void UTDBaseUpgrade::TDSpeedUpgrade()
{
    TDSetGameplayEffect(speedEffect);
}

void UTDBaseUpgrade::TDDamageUpgrade()
{
    TDSetGameplayEffect(damageEffect);
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

void UTDBaseUpgrade::TDLevelUp()
{
    UGameplayEffect* staticEffect = NewObject<UGameplayEffect>();
    staticEffect->Modifiers.Empty();
    FGameplayModifierInfo modif = FGameplayModifierInfo();
    modif.ModifierOp = EGameplayModOp::Additive;
    modif.Attribute = UTDLevelAttributeSet::GetlevelAttribute();
    modif.ModifierMagnitude = FGameplayEffectModifierMagnitude(FScalableFloat(1));
    staticEffect->Modifiers.Add(modif);
    UTDGameData::TDGetPlayerRef()->abilitySystem->ApplyGameplayEffectToSelf(staticEffect, 1, FGameplayEffectContextHandle());
    staticEffect->ConditionalBeginDestroy();
}

void UTDBaseUpgrade::TDSetGameplayEffect(TSubclassOf<UGameplayEffect> _gameplayEffect)
{
    UGameplayEffect* staticEffect = Cast<UGameplayEffect>(_gameplayEffect->GetDefaultObject());
    UTDGameData::TDGetPlayerRef()->abilitySystem->ApplyGameplayEffectToSelf(staticEffect, 1, FGameplayEffectContextHandle());
    staticEffect->ConditionalBeginDestroy();
}