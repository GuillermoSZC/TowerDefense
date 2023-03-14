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


}

void UTDPlayerHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);
    
    int32 timeRound = FGenericPlatformMath::RoundToInt32(ATDRoundManager::TDGetRoundManager()->TDGetTimeRound());

    timer->TDSetCustomText(FText::FromString(FString::FromInt(timeRound)));
}