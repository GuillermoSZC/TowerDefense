#include "UI/PauseMenu/TDPauseMenu.h"
#include "TDInventory.h"
#include "GameLogic/TDLootEnum.h"
#include "TDResourceCard.h"
#include "UI/Utilities/TDButton.h"
#include <UMG/Public/Components/WidgetSwitcher.h>

UTDPauseMenu* UTDPauseMenu::owner = nullptr;

bool UTDPauseMenu::Initialize()
{
    Super::Initialize();

    owner = this;

    return true;
}

void UTDPauseMenu::NativePreConstruct()
{
    Super::NativePreConstruct();

}

void UTDPauseMenu::NativeConstruct()
{
    Super::NativeConstruct();


    OnVisibilityChanged.AddDynamic(this, &UTDPauseMenu::TDOnVisibilityChange);

    // OnClicked Events
    inventoryButton->ownerButton->OnClicked.AddDynamic(this, &UTDPauseMenu::TDOnInventory);
    graphicsButton->ownerButton->OnClicked.AddDynamic(this, &UTDPauseMenu::TDOnGraphics);
    soundButton->ownerButton->OnClicked.AddDynamic(this, &UTDPauseMenu::TDOnSound);
    inputButton->ownerButton->OnClicked.AddDynamic(this, &UTDPauseMenu::TDOnInput);
}

UTDPauseMenu* UTDPauseMenu::TDGetPauseMenuRef()
{
    return owner;
}

void UTDPauseMenu::TDFadeIn_Implementation()
{

}

void UTDPauseMenu::TDOnVisibilityChange(ESlateVisibility _visible)
{
    if (_visible == ESlateVisibility::Visible)
    {
        TDFadeIn();
    }
    else
    {

    }
}

void UTDPauseMenu::TDOnInventory()
{
    TDSetWidgetSwitcherIndex(0);
}

void UTDPauseMenu::TDOnGraphics()
{
    TDSetWidgetSwitcherIndex(1);
}

void UTDPauseMenu::TDOnSound()
{
    TDSetWidgetSwitcherIndex(2);
}

void UTDPauseMenu::TDOnInput()
{
    TDSetWidgetSwitcherIndex(3);
}

void UTDPauseMenu::TDSetWidgetSwitcherIndex(int _value)
{
    if (IsValid(MainSwitcher) && _value > 0 && _value < MainSwitcher->GetNumWidgets() - 1)
    {
        MainSwitcher->SetActiveWidgetIndex(_value);
    }
}