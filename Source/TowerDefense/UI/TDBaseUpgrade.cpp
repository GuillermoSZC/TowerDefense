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


    buttonsArray.Add(damageUpgrade);
    buttonsArray.Add(healthUpgrade);
    buttonsArray.Add(speedUpgrade);
    buttonsArray.Add(fireUpgrade);
    buttonsArray.Add(iceUpgrade);
    buttonsArray.Add(plasmaUpgrade);

    Super::NativeConstruct();

    plasmaUpgrade->imgButton->OnClicked.AddDynamic(this, &UTDBaseUpgrade::TDPlasmaUpgrade);
    fireUpgrade->imgButton->OnClicked.AddDynamic(this, &UTDBaseUpgrade::TDFireUpgrade);
    iceUpgrade->imgButton->OnClicked.AddDynamic(this, &UTDBaseUpgrade::TDIceUpgrade);
    healthUpgrade->imgButton->OnClicked.AddDynamic(this, &UTDBaseUpgrade::TDHealthUpgrade);
    speedUpgrade->imgButton->OnClicked.AddDynamic(this, &UTDBaseUpgrade::TDSpeedUpgrade);
    damageUpgrade->imgButton->OnClicked.AddDynamic(this, &UTDBaseUpgrade::TDDamageUpgrade);
    exit->OnClicked.AddDynamic(this, &UTDBaseUpgrade::TDCloseUI);


    healthUpgrade->TDSetSound(Sound);
    speedUpgrade->TDSetSound(Sound);
    damageUpgrade->TDSetSound(Sound);
    fireUpgrade->TDSetSound(Sound);
    iceUpgrade->TDSetSound(Sound);
    plasmaUpgrade->TDSetSound(Sound);
}

void UTDBaseUpgrade::TDUpdateCost()
{
    TDUpdateBPCostWithItem(healthUpgrade, ELootItems::ArmorBP);
    TDUpdateBPCostWithItem(speedUpgrade, ELootItems::BootsBP);
    TDUpdateBPCostWithItem(damageUpgrade, ELootItems::SwordBP);

    TDUpdateGemCost(fireUpgrade, ELootItems::Fire);
    TDUpdateGemCost(iceUpgrade, ELootItems::Ice);
    TDUpdateGemCost(plasmaUpgrade, ELootItems::Plasma);

    TDUpdateInventoryToText(scrap, ELootItems::Scrap);
    TDUpdateInventoryToText(health, ELootItems::ArmorBP);
    TDUpdateInventoryToText(boots, ELootItems::BootsBP);
    TDUpdateInventoryToText(damage, ELootItems::SwordBP);
    TDUpdateInventoryToText(fire, ELootItems::Fire);
    TDUpdateInventoryToText(plasma, ELootItems::Plasma);
    TDUpdateInventoryToText(ice, ELootItems::Ice);


    TDUpdateLevelsAndElement();

}

void UTDBaseUpgrade::TDOnVisibilityChange(ESlateVisibility _visible)
{

    if (_visible == ESlateVisibility::Visible)
    {
        FUICostUpdateDelegate.Broadcast();
    }
}

void UTDBaseUpgrade::TDUpdateLevelsAndElement()
{
    ATDPlayerCharacter* player = UTDGameData::TDGetPlayerRef();

    float actualLevel = player->abilitySystem->GetNumericAttribute(UTDLevelAttributeSet::GetBootsLevelAttribute());
    int tempLevel = int(actualLevel);
    actualLevelspeedText->SetText(FText::FromString(FString::FromInt(tempLevel)));

    actualLevel = player->abilitySystem->GetNumericAttribute(UTDLevelAttributeSet::GetArmorLevelAttribute());
    tempLevel = int(actualLevel);
    actualLevelhealthText->SetText(FText::FromString(FString::FromInt(tempLevel)));


    actualLevel = player->abilitySystem->GetNumericAttribute(UTDLevelAttributeSet::GetDamageLevelAttribute());
    tempLevel = int(actualLevel);
    actualLeveldamageText->SetText(FText::FromString(FString::FromInt(tempLevel)));



    UTDElementComponent* PlayerElementComponent = ITDInterface::Execute_TDGetElementComponent(player);
    EElements actualElement = PlayerElementComponent->TDGetOwnerElement();
    UTexture2D* tempTexture = UTDGameData::TDGetGameInstance()->elementsImage[actualElement];
    actualElementImage->SetBrushFromTexture(tempTexture);





}

void UTDBaseUpgrade::TDPlasmaUpgrade()
{
    if (ITDCostInterface::Execute_TDCommitBuyUpgrade(owner->GetOwner(), ELootItems::Plasma))
    {
        TDSetElement(EElements::Plasma);
        FUICostUpdateDelegate.Broadcast();
    }
}

void UTDBaseUpgrade::TDFireUpgrade()
{
    if (ITDCostInterface::Execute_TDCommitBuyUpgrade(owner->GetOwner(), ELootItems::Fire))
    {
        TDSetElement(EElements::Fire);
        FUICostUpdateDelegate.Broadcast();
    }
}

void UTDBaseUpgrade::TDIceUpgrade()
{
    if (ITDCostInterface::Execute_TDCommitBuyUpgrade(owner->GetOwner(), ELootItems::Ice))
    {
        TDSetElement(EElements::Freeze);
        FUICostUpdateDelegate.Broadcast();
    }
}

void UTDBaseUpgrade::TDHealthUpgrade()
{
    if (ITDCostInterface::Execute_TDCommitBuyUpgrade(owner->GetOwner(), ELootItems::ArmorBP))
    {
        TDSetGameplayEffect(healthEffect);
        FUICostUpdateDelegate.Broadcast();
    }
}

void UTDBaseUpgrade::TDSpeedUpgrade()
{
    if (ITDCostInterface::Execute_TDCommitBuyUpgrade(owner->GetOwner(), ELootItems::BootsBP))
    {
        TDSetGameplayEffect(speedEffect);
        FUICostUpdateDelegate.Broadcast();
    }
}

void UTDBaseUpgrade::TDDamageUpgrade()
{
    if (ITDCostInterface::Execute_TDCommitBuyUpgrade(owner->GetOwner(), ELootItems::SwordBP))
    {
        TDSetGameplayEffect(damageEffect);
        FUICostUpdateDelegate.Broadcast();
    }
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


