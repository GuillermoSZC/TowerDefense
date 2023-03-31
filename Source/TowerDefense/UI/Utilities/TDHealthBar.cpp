#include "UI/Utilities/TDHealthBar.h"
#include "UMG/Public/Components/ProgressBar.h"


bool UTDHealthBar::Initialize()
{
    Super::Initialize();

    

    return true;
}

void UTDHealthBar::NativePreConstruct()
{
    Super::NativePreConstruct();

    if (healthBar)
    {
        healthBar->SetRenderScale(healthBarScale);
    }
}

void UTDHealthBar::NativeConstruct()
{
    Super::NativeConstruct();

}

void UTDHealthBar::TDSetBarPercentage(float _value)
{
    if (healthBar)
    {
        healthBar->SetPercent(_value);
    }
}

void UTDHealthBar::TDSetHealthBarSize(FVector2D& _value)
{
    healthBarScale = _value;
}
