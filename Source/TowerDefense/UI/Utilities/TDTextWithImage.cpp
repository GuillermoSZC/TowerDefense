// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Utilities/TDTextWithImage.h"
#include "UMG/Public/Components/SizeBox.h"

bool UTDTextWithImage::Initialize()
{
    Super::Initialize();

    quantity = 0;
    customText = FText::FromString(FString::FromInt(quantity));

    if (overridenWidth < minWidth)
    {
        overridenWidth = minWidth;
    }

    if (overridenHeight < minHeight)
    {
        overridenHeight = minHeight;
    }

    return true;
}

void UTDTextWithImage::NativePreConstruct()
{
    Super::NativePreConstruct();

    if (elementText)
    {
        elementText->TDSetCustomText(customText);
    }

    if (elementBox)
    {
        elementBox->bOverride_MinDesiredWidth = true;
        elementBox->SetMinDesiredWidth(useOverridenWidth ? overridenWidth : minWidth);
        elementBox->bOverride_MinDesiredHeight = true;
        elementBox->SetMinDesiredHeight(useOverridenHeight ? overridenHeight : minHeight);
    }
}

void UTDTextWithImage::NativeConstruct()
{
    Super::NativeConstruct();


}

void UTDTextWithImage::TDSetText(FText _text)
{
    customText = _text;
}

FText UTDTextWithImage::TDGetText()
{
    return customText;
}

void UTDTextWithImage::TDSetQuantity(int32 _value)
{
    quantity = _value;
}

int32 UTDTextWithImage::TDGetQuantity()
{
    return quantity;
}
