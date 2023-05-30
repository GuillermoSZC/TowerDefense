#include "UI/PauseMenu/TDResourceCard.h"
#include <Engine/Texture2D.h>
#include <UMG/Public/Components/Image.h>
#include "Character/TDPlayerCharacter.h"
#include "GameLogic/TDGameData.h"
#include "UI/Utilities/TDRichTextBlock.h"

bool UTDResourceCard::Initialize()
{
    Super::Initialize();

    return true;
}

void UTDResourceCard::NativePreConstruct()
{
    Super::NativePreConstruct();

    TDSetImage(resourceTex);
}

void UTDResourceCard::NativeConstruct()
{
    Super::NativeConstruct();

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

FText UTDResourceCard::TDGetTextFromItem(ELootItems _item)
{
    ATDPlayerCharacter* playerRef = UTDGameData::TDGetPlayerRef();
    int32 intTemp = playerRef->TDGetAmountItemByItem(_item);
    FString StringTemp = FString::FromInt(intTemp);
    FText textTemp = FText::FromString(StringTemp);

    return textTemp;
}

void UTDResourceCard::TDUpdateInventoryToText(UTDRichTextBlock* _text, ELootItems _item)
{
    _text->SetText(TDGetTextFromItem(_item));
}
