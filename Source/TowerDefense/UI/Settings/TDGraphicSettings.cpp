#include "UI/Settings/TDGraphicSettings.h"
#include "UI/Utilities/TDRowStringList.h"
#include <UMG/Public/Components/ComboBoxString.h>
#include <GameFramework/GameUserSettings.h>

bool UTDGraphicSettings::Initialize()
{
    Super::Initialize();

    gameUserSettings = GEngine->GetGameUserSettings();

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
    if (_string == "Full Screen")
    {
        gameUserSettings->SetFullscreenMode(EWindowMode::Fullscreen);
    }
    else if (_string == "Borderless")
    {
        gameUserSettings->SetFullscreenMode(EWindowMode::WindowedFullscreen);
    }
    else if (_string == "Windowed")
    {
        gameUserSettings->SetFullscreenMode(EWindowMode::Windowed);
    }

    gameUserSettings->ApplyResolutionSettings(false);

}

void UTDGraphicSettings::TDOnResolutionChanged(FString _string, ESelectInfo::Type _select)
{
    FIntPoint screenResolution;

    if (_string == "1920x1080")
    {        
        screenResolution.X = 1920;
        screenResolution.Y = 1080;

        
        gameUserSettings->SetScreenResolution(screenResolution);
    }
    else if (_string == "1280x720")
    {
        screenResolution.X = 1280;
        screenResolution.Y = 720;

        gameUserSettings->SetScreenResolution(screenResolution);
    }
    else if (_string == "2560x1440")
    {
        screenResolution.X = 2560;
        screenResolution.Y = 1440;

        gameUserSettings->SetScreenResolution(screenResolution);
    }

    gameUserSettings->ApplyResolutionSettings(false);
    gameUserSettings->ConfirmVideoMode();
}

void UTDGraphicSettings::TDOnFrameCapChanged(FString _string, ESelectInfo::Type _select)
{
//     switch (_string)
//     {
//     case "30":
//     {
// 
//     }
//     break;
//     case "60":
//     {
// 
//     }
//     break;
//     case "120":
//     {
// 
//     }
//     break;
//     case "Unlimited":
//     {
// 
//     }
//     break;
//     default:
//     {
// 
//     }
//     break;
//     }
}
