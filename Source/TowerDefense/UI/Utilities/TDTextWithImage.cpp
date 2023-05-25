// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Utilities/TDTextWithImage.h"
#include "UMG/Public/Components/SizeBox.h"
#include "UMG/Public/Components/Image.h"
#include "Engine/Texture2D.h"

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
        // elementBox->bOverride_MinDesiredWidth = true; -- DEPRECATED
        elementBox->SetMinDesiredWidth(useOverridenWidth ? overridenWidth : minWidth);
        // elementBox->bOverride_MinDesiredHeight = true; -- DEPRECATED
        elementBox->SetMinDesiredHeight(useOverridenHeight ? overridenHeight : minHeight);
    }

    if (ownerImage)
    {
        ownerImage->SetBrushFromTexture(customTexture);
    }
}

void UTDTextWithImage::NativeConstruct()
{
    Super::NativeConstruct();


}

void UTDTextWithImage::TDSetText(FText _text)
{
    customText = _text;
    
    elementText->TDSetCustomText(customText);
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

void UTDTextWithImage::TDSetTexture(UTexture2D* _texture)
{
    if (_texture != nullptr)
    {
        customTexture = _texture;
        ownerImage->SetBrushFromTexture(customTexture);
    }
}

UTexture2D* UTDTextWithImage::TDGetTexture(UTexture2D* _texture)
{
    return _texture;
}
