#include "GameLogic/TDMainMenuController.h"
#include "UI/MainMenu/TDMainMenu.h"

void ATDMainMenuController::BeginPlay()
{
    Super::BeginPlay();

    if (mainMenuClass)
    {
        mainMenuRef = CreateWidget<UTDMainMenu>(this, mainMenuClass);

        if (mainMenuRef)
        {
            FInputModeGameAndUI inputMode;
            mainMenuRef->AddToViewport(0);
            SetInputMode(inputMode);
            bShowMouseCursor = true;
        }
    }
}
