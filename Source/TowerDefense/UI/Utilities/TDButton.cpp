#include "UI/Utilities/TDButton.h"
#include "TDText.h"
#include "Components/Button.h"
#include "TDRichTextBlock.h"

bool UTDButton::Initialize()
{
    Super::Initialize();

    return true;
}
void UTDButton::NativePreConstruct()
{
    Super::NativePreConstruct();

    if (richText)
    {
        richText->SetText(useButtonText ? buttonText : FText::FromString(TEXT("Button <Title>Text</>")));

        if (textStyleData && useCustomTextStyleData)
        {
            richText->SetTextStyleSet(textStyleData);
        }
    }
}

void UTDButton::NativeConstruct()
{
    Super::NativeConstruct();

}