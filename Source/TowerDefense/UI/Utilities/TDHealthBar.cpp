#include "UI/Utilities/TDHealthBar.h"
#include "UMG/Public/Components/ProgressBar.h"


bool UTDHealthBar::Initialize()
{
    Super::Initialize();

    TDSetHealthBarSize(healthBarScale);

    return true;
}

void UTDHealthBar::NativePreConstruct()
{
    Super::NativePreConstruct();

    TDSetProgressBarStyle(ProgressBarStyle);
}

void UTDHealthBar::NativeConstruct()
{
    Super::NativeConstruct();
}

void UTDHealthBar::TDSetBarPercentage(float _percentage, float _actualHP)
{
    if (healthBar)
    {
        healthBar->SetPercent(_percentage);
    }
}

void UTDHealthBar::TDSetHealthBarSize(FVector2D& _value)
{
    if (healthBar)
    {
        healthBar->SetRenderScale(_value);
    }
}

void UTDHealthBar::TDSetProgressBarStyle(FProgressBarStyle& _progressBarStyle)
{
    ProgressBarStyle = _progressBarStyle;

    if (healthBar)
    {
        healthBar->SetWidgetStyle(ProgressBarStyle);
    }
}
