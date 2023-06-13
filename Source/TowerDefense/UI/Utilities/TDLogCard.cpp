// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Utilities/TDLogCard.h"
#include "UMG/Public/Components/Image.h"
#include "UMG/Public/Components/Border.h"
#include "TDText.h"

bool UTDLogCard::Initialize()
{
    Super::Initialize();

    return true;
}

void UTDLogCard::NativePreConstruct()
{
    Super::NativePreConstruct();

    if (ItemMapImage.IsEmpty())
    {
        
        for (ELootItems item : TEnumRange<ELootItems>())
        {
            if (item != ELootItems::None)
            {
                ItemMapImage.Add(item);
            }
        }
    }

}

void UTDLogCard::NativeConstruct()
{

    Super::NativeConstruct();

}

void UTDLogCard::TDPrepareCard(FTDItemStruct _item)
{

    ownerImage->SetBrushFromTexture(ItemMapImage[_item.dropLoot]);
    ownerBorder->SetBrushColor(ColorBackgroundRarity[_item.categoryLoot]);
    ownerText->TDSetCustomText(FText::FromString("+" + FString::FromInt(_item.amountLoot)));
   
}
