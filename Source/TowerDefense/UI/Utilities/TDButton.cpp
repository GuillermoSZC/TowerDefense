#include "UI/Utilities/TDButton.h"
#include "TDText.h"
#include "Components/Button.h"
#include "TDRichTextBlock.h"


bool UTDButton::Initialize()
{
    Super::Initialize();

    if (ownerButton)
    {
        ownerButton->OnClicked.AddDynamic(this, &UTDButton::TDPlayButtonSound);
    }


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

    TDSetButtonStyle(ButtonStyle);

}

void UTDButton::NativeConstruct()
{
    Super::NativeConstruct();


}

void UTDButton::TDSetButtonStyle(FButtonStyle& _buttonStyle)
{
    ButtonStyle = _buttonStyle;

    if (ownerButton)
    {
        ownerButton->SetStyle(ButtonStyle);
    }
}


void UTDButton::TDSetPadding(FMargin _padding)
{
    ownPadding = _padding;
    SetPadding(ownPadding);
}

void UTDButton::TDSetText(FText _text)
{
    buttonText = _text;
    useButtonText = true;
    richText->SetText(buttonText);
}

FText UTDButton::TDGetText() const
{
    return buttonText;
}

void UTDButton::TDSetFont(UDataTable* _font)
{
    useCustomTextStyleData = true;
    textStyleData = _font;
}

bool UTDButton::TDGetButtonAnimated() const
{
    return hasBeenAnimated;
}

void UTDButton::TDButtonAnimated(bool _value)
{
    hasBeenAnimated = _value;
}

bool UTDButton::TDGetIsActive() const
{
    return isActive;
}

void UTDButton::TDSetIsActive(bool _value)
{
    isActive = _value;
}

void UTDButton::TDClickedToRight_Implementation()
{

}

void UTDButton::TDUnselected_Implementation()
{

}
