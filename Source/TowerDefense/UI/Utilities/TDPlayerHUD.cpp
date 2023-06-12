#include "UI/Utilities/TDPlayerHUD.h"
#include "GameLogic/TDRoundManager.h"
#include "GameLogic/TDGameData.h"
#include "GameLogic/TDGameInstance.h"
#include "GameLogic/TDElementComponent.h"
#include "Character/TDCharacter.h"
#include "Interfaces/TDInterface.h"
#include "UMG/Public/Components/Image.h"
#include "UI/Utilities/TDTextWithImage.h"
#include "TDText.h"
#include "TDHealthBar.h"
#include "Character/TDPlayerCharacter.h"
#include "TDLogCard.h"



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

    TDInitialize();
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

void UTDPlayerHUD::TDInitialize()
{

    elementsArray.Add(firstElement);
    elementsArray.Add(secondElement);
    elementsArray.Add(thirdElement);

    roundManager = UTDGameData::TDGetRoundManager();

    if (roundManager)
    {
        roundManager->FOnBuyPhaseStartDelegate.AddUniqueDynamic(this, &UTDPlayerHUD::TDSetBuyUI);
        roundManager->FOnCombatPhaseStartDelegate.AddUniqueDynamic(this, &UTDPlayerHUD::TDSetCombatUI);
        roundManager->FOnElementSelectionDelegate.AddUniqueDynamic(this, &UTDPlayerHUD::TDSetElementsUI);
        roundManager->FOnEnemyKillDelegate.AddUniqueDynamic(this, &UTDPlayerHUD::TDSetEnemyCounter);
    }

    ATDCharacter* ownerRef = GetOwningPlayerPawn<ATDCharacter>();

    if (ownerRef)
    {
        ownerRef->FOnHealthChangeDelegate.AddUniqueDynamic(healthBar, &UTDHealthBar::TDSetBarPercentage);
        ownerRef->FOnHealthChangeDelegate.AddUniqueDynamic(this, &UTDPlayerHUD::TDUpdateHealthNumber);
        ITDInterface::Execute_TDGetElementComponent(ownerRef)->OnElementChangeDelegate.AddUniqueDynamic(this, &UTDPlayerHUD::TDSetPlayerElement);
    }

    if (phase)
    {
        phase->TDSetCustomText(FText::FromString("Buy Phase"));
    }




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
    roundNum->TDSetCustomText(FText::FromString(FString::FromInt(_value)));
    TDSetElementsVisibility(ESlateVisibility::Visible);
}

void UTDPlayerHUD::TDSetElementsUI(TArray<EElements>& _elements)
{
    int arraySize = _elements.Num();

    for (int i = 0; i <= (elementsArray.Num() - 1); ++i)
    {
        if (i <= arraySize - 1)
        {
            UTexture2D* tempTexture = UTDGameData::TDGetGameInstance()->elementsImage[_elements[i]];
            elementsArray[i]->SetVisibility(ESlateVisibility::Visible);
            elementsArray[i]->SetBrushFromTexture(tempTexture);
        }
        else
        {
            elementsArray[i]->SetVisibility(ESlateVisibility::Collapsed);
        }
    }
}

void UTDPlayerHUD::TDSetElementsVisibility(ESlateVisibility _visibility)
{
    timer->SetVisibility(_visibility); // @TODO: Quitar funcion (?)
}

void UTDPlayerHUD::TDSetPlayerElement(EElements _element)
{
    UTexture2D* texture = UTDGameData::TDGetGameInstance()->elementsImage[_element];
    playerElement->SetBrushFromTexture(texture);
}

void UTDPlayerHUD::TDSetEnemyCounter(int32 _counter)
{
    enemyCounter->TDSetCustomText(FText::FromString(FString::FromInt(_counter)));
}

void UTDPlayerHUD::TDUpdateHealthNumber(float _percentage, float _actualHp)
{
    healthNumber->TDSetCustomText(FText::FromString(FString::SanitizeFloat(_actualHp)));
}


void UTDPlayerHUD::TDVisibilityToShopUIs(ESlateVisibility _visibility)
{
    healthBar->SetVisibility(_visibility);
    healthNumber->SetVisibility(_visibility);
    healthBarContainer->SetVisibility(_visibility);
    enemyCounter->SetVisibility(_visibility);
    enemyText->SetVisibility(_visibility);
    roundText->SetVisibility(_visibility);
    roundNum->SetVisibility(_visibility);
}

