#include "UI/Utilities/TDCustomSlider.h"
#include <UMG/Public/Components/Slider.h>
#include <UMG/Public/Components/ProgressBar.h>

bool UTDCustomSlider::Initialize()
{
    Super::Initialize();

    customSlider->OnValueChanged.AddDynamic(this, &UTDCustomSlider::TDUpdateValue);

    return true;
}

void UTDCustomSlider::NativePreConstruct()
{
    Super::NativePreConstruct();

}

void UTDCustomSlider::NativeConstruct()
{
    Super::NativeConstruct();

}

void UTDCustomSlider::TDUpdateValue(float _value)
{
    customProgressBar->SetPercent(_value);
}
