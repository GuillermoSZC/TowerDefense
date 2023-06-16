#include "UI/TDGameOver.h"

bool UTDGameOver::Initialize()
{
    Super::Initialize();

    OnVisibilityChanged.AddDynamic(this, &UTDGameOver::TDVisibilityGameOver);    

    return true;
}

void UTDGameOver::NativePreConstruct()
{
    Super::NativePreConstruct();

}

void UTDGameOver::NativeConstruct()
{
    Super::NativeConstruct();

}

void UTDGameOver::TDVisibilityGameOver(ESlateVisibility _visibility)
{
    if (_visibility == ESlateVisibility::Visible)
    {
        TDFadeIn();
    }
}