#include "UI/TDMainMenu.h"
#include "Utilities/TDButton.h"

bool UTDMainMenu::Initialize()
{
    Super::Initialize();

    return true;
}

void UTDMainMenu::NativePreConstruct()
{
    Super::NativePreConstruct();


}

void UTDMainMenu::NativeConstruct()
{
    Super::NativeConstruct();

    playButton->ownerButton->OnClicked.AddUniqueDynamic(this, &UTDMainMenu::TDOpenLevel);
}
