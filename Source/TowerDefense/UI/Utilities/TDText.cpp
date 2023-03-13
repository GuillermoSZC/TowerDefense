// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Utilities/TDText.h"
#include "Components/RichTextBlock.h"
#include "Engine/DataTable.h"

bool UTDText::Initialize()
{
    Super::Initialize();

    return true;
}

void UTDText::NativePreConstruct()
{
    Super::NativePreConstruct();

    if (customRichText)
    {
        customRichText->SetText(useCustomText ? customText : FText::FromString(TEXT("Example <Title>Text</>")));
    }

    if (useCustomTextStyleData)
    {
        TDSetCustomTextStyle(textStyleData);
    }
}

void UTDText::NativeConstruct()
{
    Super::NativeConstruct();

}

void UTDText::TDSetCustomText(FText _newText)
{
    customText = _newText;
    customRichText->SetText(customText);
}

void UTDText::TDSetCustomTextStyle(UDataTable* _newTextStyleData)
{
    customRichText->SetTextStyleSet(_newTextStyleData);
}
