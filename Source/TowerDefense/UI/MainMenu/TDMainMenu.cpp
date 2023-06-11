#include "UI/MainMenu/TDMainMenu.h"
#include "UI/Utilities/TDButton.h"
#include <UMG/Public/Components/WidgetSwitcher.h>
#include <Kismet/KismetSystemLibrary.h>

bool UTDMainMenu::Initialize()
{
    Super::Initialize();

    if (normalMode)
    {
        normalMode->ownerButton->OnClicked.AddDynamic(this, &UTDMainMenu::TDLevelsSelector);
    }

    if (infiniteMode)
    {
        infiniteMode->ownerButton->OnClicked.AddDynamic(this, &UTDMainMenu::TDInfiniteLevelsSelector);
    }

    if (graphics)
    {
        graphics->ownerButton->OnClicked.AddDynamic(this, &UTDMainMenu::TDGraphics);
    }

    if (sound)
    {
        sound->ownerButton->OnClicked.AddDynamic(this, &UTDMainMenu::TDSound);
    }

    if (input)
    {
        input->ownerButton->OnClicked.AddDynamic(this, &UTDMainMenu::TDInput);
    }

    if (exit)
    {
        exit->ownerButton->OnClicked.AddDynamic(this, &UTDMainMenu::TDExit);
    }

    return true;
}

void UTDMainMenu::NativePreConstruct()
{
    Super::NativePreConstruct();


}

void UTDMainMenu::NativeConstruct()
{
    Super::NativeConstruct();


}

void UTDMainMenu::TDLevelsSelector()
{
    infiniteMode->TDUnselected();
    graphics->TDUnselected();
    sound->TDUnselected();
    input->TDUnselected();
    normalMode->TDClickedToRight();

    mainMenuSwitcher->SetActiveWidgetIndex(1);
}

void UTDMainMenu::TDInfiniteLevelsSelector()
{
    normalMode->TDUnselected();
    graphics->TDUnselected();
    sound->TDUnselected();
    input->TDUnselected();
    infiniteMode->TDClickedToRight();

    mainMenuSwitcher->SetActiveWidgetIndex(2);
}

void UTDMainMenu::TDGraphics()
{
    normalMode->TDUnselected();
    sound->TDUnselected();
    input->TDUnselected();
    infiniteMode->TDUnselected();
    graphics->TDClickedToRight();

    mainMenuSwitcher->SetActiveWidgetIndex(3);
}

void UTDMainMenu::TDSound()
{
    normalMode->TDUnselected();
    graphics->TDUnselected();
    input->TDUnselected();
    infiniteMode->TDUnselected();
    sound->TDClickedToRight();

    mainMenuSwitcher->SetActiveWidgetIndex(4);
}

void UTDMainMenu::TDInput()
{
    normalMode->TDUnselected();
    graphics->TDUnselected();
    sound->TDUnselected();
    infiniteMode->TDUnselected();
    input->TDClickedToRight();

    mainMenuSwitcher->SetActiveWidgetIndex(5);
}
void UTDMainMenu::TDExit()
{
    UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, false);
}