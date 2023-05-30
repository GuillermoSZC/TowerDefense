#include "UI/PauseMenu/TDPauseMenu.h"
#include "TDInventory.h"
#include "GameLogic/TDLootEnum.h"
#include "TDResourceCard.h"

bool UTDPauseMenu::Initialize()
{
    Super::Initialize();

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
    FUIUpdateResourcesDelegate.AddDynamic(this, &UTDPauseMenu::TDUpdateCards);
}

void UTDPauseMenu::TDOnVisibilityChange(ESlateVisibility _visible)
{
    if (_visible == ESlateVisibility::Visible)
    {
        FUIUpdateResourcesDelegate.Broadcast();
    }
}

void UTDPauseMenu::TDUpdateCards()
{
    if (inventory)
    {
        // inventory->healthCard->TDUpdateResource(ELootItems::ArmorBP);
    }
}
