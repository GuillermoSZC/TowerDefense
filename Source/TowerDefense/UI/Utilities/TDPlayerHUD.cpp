#include "UI/Utilities/TDPlayerHUD.h"
#include "GameLogic/TDRoundManager.h"

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

    roundManager = ATDRoundManager::TDGetRoundManager();

    if (roundManager)
    {
        roundManager->FOnBuyPhaseStartDelegate.AddUniqueDynamic(this, &UTDPlayerHUD::TDSetBuyUI);
        roundManager->FOnCombatPhaseStartDelegate.AddUniqueDynamic(this, &UTDPlayerHUD::TDSetCombatUI);
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
    timer->SetVisibility(ESlateVisibility::Collapsed);
}

void UTDPlayerHUD::TDSetBuyUI(int32 _value)
{
    phase->TDSetCustomText(FText::FromString("Buy Phase"));
    timer->SetVisibility(ESlateVisibility::Visible);
}