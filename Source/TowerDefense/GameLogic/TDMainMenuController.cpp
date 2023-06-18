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
            mainMenuRef->AddToViewport(0);
            UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(this, mainMenuRef);
            bShowMouseCursor = true;
        }
    }
}
