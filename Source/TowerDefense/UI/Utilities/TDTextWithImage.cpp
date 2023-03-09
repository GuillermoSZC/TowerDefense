// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Utilities/TDTextWithImage.h"

bool UTDTextWithImage::Initialize()
{
    Super::Initialize();

    quantity = 0;
    customText = FText::FromString(FString::FromInt(quantity));

    return true;
}

void UTDTextWithImage::NativePreConstruct()
{
    Super::NativePreConstruct();


}

void UTDTextWithImage::NativeConstruct()
{
    Super::NativeConstruct();

    if (textElement)
    {
        textElement->TDSetCustomText(customText);
    }
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
