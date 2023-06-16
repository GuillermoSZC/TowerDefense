#include "UI/PauseMenu/TDPauseMenu.h"
#include "TDInventory.h"
#include "GameLogic/TDLootEnum.h"
#include "TDResourceCard.h"
#include "UI/Utilities/TDButton.h"
#include <UMG/Public/Components/WidgetSwitcher.h>
#include <Kismet/KismetSystemLibrary.h>
#include <Kismet/GameplayStatics.h>

UTDPauseMenu* UTDPauseMenu::owner = nullptr;

bool UTDPauseMenu::Initialize()
{
    Super::Initialize();

    owner = this;

    // OnClicked Events
    if (inventoryButton)
    {
        inventoryButton->ownerButton->OnClicked.AddDynamic(this, &UTDPauseMenu::TDOnInventory);
    }

    if (graphicsButton)
    {
        graphicsButton->ownerButton->OnClicked.AddDynamic(this, &UTDPauseMenu::TDOnGraphics);
    }

    if (soundButton)
    {
        soundButton->ownerButton->OnClicked.AddDynamic(this, &UTDPauseMenu::TDOnSound);
    }

    if (inputButton)
    {
        inputButton->ownerButton->OnClicked.AddDynamic(this, &UTDPauseMenu::TDOnInput);
    }

    if (mainMenu)
    {
        mainMenu->ownerButton->OnClicked.AddDynamic(this, &UTDPauseMenu::TDGoToMainMenu);
    }

    if (exit)
    {
        exit->ownerButton->OnClicked.AddDynamic(this, &UTDPauseMenu::TDExitGame);
    }

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
    OnVisibilityChanged.AddDynamic(inventory, &UTDInventory::TDUpdateScrap);


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
    if (IsValid(MainSwitcher) && _value >= 0 && _value < MainSwitcher->GetNumWidgets())
    {
        MainSwitcher->SetActiveWidgetIndex(_value);
    }
}

void UTDPauseMenu::TDExitGame()
{
    UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, false);
}