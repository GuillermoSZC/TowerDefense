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
    mainMenuSwitcher->SetActiveWidgetIndex(1);
}

void UTDMainMenu::TDInfiniteLevelsSelector()
{
    mainMenuSwitcher->SetActiveWidgetIndex(2);
}

void UTDMainMenu::TDGraphics()
{

}

void UTDMainMenu::TDSound()
{

}

void UTDMainMenu::TDInput()
{


}
void UTDMainMenu::TDExit()
{
    UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, false);
}