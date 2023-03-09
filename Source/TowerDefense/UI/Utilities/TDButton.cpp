// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Utilities/TDButton.h"
#include "TDText.h"
#include "Components/Button.h"


bool UTDButton::Initialize()
{
    Super::Initialize();

    return true;
}

void UTDButton::NativePreConstruct()
{
    Super::NativePreConstruct();

//     if (ownerButton)
//     {
//         ownerButton->SetBackgroundColor(FLinearColor::FromSRGBColor(FColor::White));
//         ownerButton->SetRenderOpacity(showButtonBackground ? 1 : 0);
//     }

    if (textButton)
    {
        textButton->TDSetCustomText(useButtonText ? buttonText : FText::FromString(TEXT("Example <Title>Text</>")));
    }

    if (useCustomTextStyleData)
    {
        textButton->TDSetCustomTextStyle(textStyleData);
    }
}

void UTDButton::NativeConstruct()
{
    Super::NativeConstruct();


}
