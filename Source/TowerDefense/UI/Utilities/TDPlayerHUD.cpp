#include "UI/Utilities/TDPlayerHUD.h"
#include "GameLogic/TDRoundManager.h"
#include "GameLogic/TDGameData.h"
#include "Character/TDCharacter.h"

bool UTDPlayerHUD::Initialize()
{
    Super::Initialize();

    return true;
}

void UTDPlayerHUD::NativePreConstruct()
{
    Super::NativePreConstruct();

}

void UTDPlayerHUD::NativeConstruct()
{
    Super::NativeConstruct();

    roundManager = UTDGameData::TDGetRoundManager();

    if (roundManager)
    {
        roundManager->FOnBuyPhaseStartDelegate.AddUniqueDynamic(this, &UTDPlayerHUD::TDSetBuyUI);
        roundManager->FOnCombatPhaseStartDelegate.AddUniqueDynamic(this, &UTDPlayerHUD::TDSetCombatUI);
    }

    ATDCharacter* ownerRef = GetOwningPlayerPawn<ATDCharacter>();

    if (ownerRef)
    {
        ownerRef->FOnHealthChangeDelegate.AddUniqueDynamic(healthBar, &UTDHealthBar::TDSetBarPercentage);        
    }

    if (phase)
    {
        phase->TDSetCustomText(FText::FromString("Buy Phase"));
    }
}

void UTDPlayerHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);

    int32 timeRound = 0;

    if (roundManager)
    {
        timeRound = FGenericPlatformMath::RoundToInt32(roundManager->TDGetTimeRound());
    }

    timer->TDSetCustomText(FText::FromString(FString::FromInt(timeRound)));
}

void UTDPlayerHUD::TDSetCombatUI(int32 _value)
{
    phase->TDSetCustomText(FText::FromString("Combat Phase"));
    roundNum->TDSetCustomText(FText::FromString(FString::FromInt(_value)));
    TDSetElementsVisibility(ESlateVisibility::Collapsed);
}

void UTDPlayerHUD::TDSetBuyUI(int32 _value)
{
    phase->TDSetCustomText(FText::FromString("Buy Phase"));
    TDSetElementsVisibility(ESlateVisibility::Visible);
}

void UTDPlayerHUD::TDSetElementsVisibility(ESlateVisibility _visibility)
{
    timer->SetVisibility(_visibility);
    scrap->SetVisibility(_visibility);
    swordBlueprint->SetVisibility(_visibility);
    armorBlueprint->SetVisibility(_visibility);
    bootsBlueprint->SetVisibility(_visibility);
    ballistaBlueprint->SetVisibility(_visibility);
    sonicTowerBlueprint->SetVisibility(_visibility);
    deathRayTowerBlueprint->SetVisibility(_visibility);
    speedTowerBlueprint->SetVisibility(_visibility);
    damageTowerBlueprint->SetVisibility(_visibility);
    fireGem->SetVisibility(_visibility);
    iceGem->SetVisibility(_visibility);
    plasmaGem->SetVisibility(_visibility);
}
