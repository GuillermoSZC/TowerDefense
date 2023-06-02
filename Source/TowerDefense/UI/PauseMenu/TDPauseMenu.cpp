#include "UI/PauseMenu/TDPauseMenu.h"
#include "TDInventory.h"
#include "GameLogic/TDLootEnum.h"
#include "TDResourceCard.h"

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

