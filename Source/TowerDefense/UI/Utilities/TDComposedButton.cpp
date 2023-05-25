#include "UI/Utilities/TDComposedButton.h"
#include <UMG/Public/Blueprint/WidgetLayoutLibrary.h>
#include "TDTextWithImage.h"
#include "UMG/Public/Components/Border.h"

bool UTDComposedButton::Initialize()
{
    Super::Initialize();

    return true;
}

void UTDComposedButton::NativePreConstruct()
{
    Super::NativePreConstruct();

    if (scrap && bps && gems)
    {
        scrap->TDSetText(FText::FromString("<Black>123</>"));
        bps->TDSetText(FText::FromString("<Black>123</>"));
        gems->TDSetText(FText::FromString("<Black>123</>"));

        switch (resources)
        {
        case ETDResources::ScrapAndBlueprints:
            scrap->SetVisibility(ESlateVisibility::Visible);
            bps->SetVisibility(ESlateVisibility::Visible);
            gems->SetVisibility(ESlateVisibility::Collapsed);
            break;
        case ETDResources::Gems:
            scrap->SetVisibility(ESlateVisibility::Collapsed);
            bps->SetVisibility(ESlateVisibility::Collapsed);
            gems->SetVisibility(ESlateVisibility::Visible);
            break;
        default:
            ensure(false);
            break;
        }
    }

    AvalibleBuyColor = FLinearColor(0.55f, 0.2f, 0, 1.f);
    NotAvalibleBuyColor = FLinearColor(1.f, 0.f, 0.02f, 1.f);

}

void UTDComposedButton::NativeConstruct()
{
    Super::NativeConstruct();



}

void UTDComposedButton::TDCanAfford(bool _CanAfford)
{
    if (_CanAfford)
    {
        SetVisibility(ESlateVisibility::Visible);
        borderBase->SetBrushColor(AvalibleBuyColor);
    }
    else
    {
        borderBase->SetBrushColor(NotAvalibleBuyColor);
        SetVisibility(ESlateVisibility::HitTestInvisible);


    }
}



