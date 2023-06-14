#include "UI/PauseMenu/TDResourceCard.h"
#include <Engine/Texture2D.h>
#include <UMG/Public/Components/Image.h>
#include "Character/TDPlayerCharacter.h"
#include "GameLogic/TDGameData.h"
#include "UI/Utilities/TDRichTextBlock.h"
#include <UMG/Public/Components/Border.h>
#include "TDPauseMenu.h"

UTDResourceCard::UTDResourceCard()
{
    resourceImage = CreateDefaultSubobject<UImage>("Image");
    backgroundMain = CreateDefaultSubobject<UBorder>("Border");
}

bool UTDResourceCard::Initialize()
{
    Super::Initialize();

    return true;
}

void UTDResourceCard::NativePreConstruct()
{
    Super::NativePreConstruct();

    TDSetImage(resourceTex);



    SetPadding(customPadding);
}

void UTDResourceCard::NativeConstruct()
{
    Super::NativeConstruct();

    UTDPauseMenu::TDGetPauseMenuRef()->OnVisibilityChanged.AddDynamic(this, &UTDResourceCard::TDOnVisibilityChange);

}

void UTDResourceCard::TDSetImage(UTexture2D* _tex)
{
    if (IsValid(_tex))
    {
        resourceTex = _tex;
        resourceImage->SetBrushFromTexture(resourceTex);
    }
}

void UTDResourceCard::TDUpdateResource(ELootItems _item)
{
    TDUpdateInventoryToText(resourceText, _item);
}

void UTDResourceCard::TDSetPadding(FMargin _padding)
{
    customPadding = _padding;
    SetPadding(customPadding);
}

void UTDResourceCard::TDSetResourceCardAttributes(FTDResourceCardParameters& _row, UTDResourceCard* _card)
{
    _card->TDSetImage(_row.image);
    _card->backgroundMain->SetBrushColor(_row.color);
    _card->TDSetPadding(_row.padding);
    _card->TDSetItem(_row.resource);
}

void UTDResourceCard::TDSetItem(ELootItems _item)
{
    item = _item;
}

ELootItems UTDResourceCard::TDGetItem() const
{
    return item;
}


FText UTDResourceCard::TDGetTextFromItem(ELootItems _item)
{
    ATDPlayerCharacter* playerRef = UTDGameData::TDGetPlayerRef();
    int32 intTemp = playerRef->TDGetAmountItemByItem(_item);
    FString StringTemp = FString::FromInt(intTemp);
    FText textTemp = FText::FromString("<Black>" + StringTemp + "</>");

    return textTemp;
}

void UTDResourceCard::TDUpdateInventoryToText(UTDRichTextBlock* _text, ELootItems _item)
{
    _text->SetText(TDGetTextFromItem(_item));
}

void UTDResourceCard::TDOnVisibilityChange(ESlateVisibility _visibility)
{
    if (_visibility == ESlateVisibility::Visible)
    {
        TDUpdateResource(TDGetItem());
    }
}