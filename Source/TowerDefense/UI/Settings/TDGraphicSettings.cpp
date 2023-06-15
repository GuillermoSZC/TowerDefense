#include "UI/Settings/TDGraphicSettings.h"
#include "UI/Utilities/TDRowStringList.h"
#include <UMG/Public/Components/ComboBoxString.h>

bool UTDGraphicSettings::Initialize()
{
    Super::Initialize();

    if (screenMode)
    {
        screenMode->stringList->OnSelectionChanged.AddDynamic(this, &UTDGraphicSettings::TDOnScreenModeChanged);
    }

    if (resolution)
    {
        resolution->stringList->OnSelectionChanged.AddDynamic(this, &UTDGraphicSettings::TDOnResolutionChanged);
    }

    if (frameCap)
    {
        frameCap->stringList->OnSelectionChanged.AddDynamic(this, &UTDGraphicSettings::TDOnFrameCapChanged);
    }

    return true;
}

void UTDGraphicSettings::NativePreConstruct()
{
    Super::NativePreConstruct();


}

void UTDGraphicSettings::NativeConstruct()
{
    Super::NativeConstruct();

}

void UTDGraphicSettings::TDOnScreenModeChanged(FString _string, ESelectInfo::Type _select)
{
    
}

void UTDGraphicSettings::TDOnResolutionChanged(FString _string, ESelectInfo::Type _select)
{

}

void UTDGraphicSettings::TDOnFrameCapChanged(FString _string, ESelectInfo::Type _select)
{

}
