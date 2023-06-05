#include "UI/PauseMenu/TDInventory.h"
#include "GameLogic/TDLootEnum.h"
#include "TDResourceCard.h"
#include "GameLogic/TDInventoryEnum.h"
#include "GameLogic/Structs/TDResourceCardParameters.h"
#include "UI/Utilities/TDTwoButtonHorizontalBox.h"
#include <UMG/Public/Components/VerticalBox.h>
#include <Engine/DataTable.h>
#include <UMG/Public/Blueprint/WidgetTree.h>
#include <UMG/Public/Components/Button.h>
#include "UI/Utilities/TDTextWithImage.h"

bool UTDInventory::Initialize()
{
    Super::Initialize();

    return true;
}

void UTDInventory::NativePreConstruct()
{
    Super::NativePreConstruct();

    TDInitComponents();
}

void UTDInventory::NativeConstruct()
{
    Super::NativeConstruct();
}

void UTDInventory::TDUpdateScrap(ESlateVisibility _visibility)
{
    if (_visibility == ESlateVisibility::Visible)
    {
        ATDPlayerCharacter* playerRef = UTDGameData::TDGetPlayerRef();
        int32 inttemp = playerRef->TDGetAmountItemByItem(ELootItems::Scrap);
        FString StringTemp = FString::FromInt(inttemp);
        FText textTemp = FText::FromString(StringTemp);
        scrapText->TDSetText(textTemp);
    }
}

void UTDInventory::TDInitComponents()
{
    TDFillStructures();
}

void UTDInventory::TDAddResourceCard(UTDResourceCard* _card, UVerticalBox* _verticalBox)
{
    UButton* button = NewObject<UButton>(UButton::StaticClass(), "Button");


    if (_verticalBox->GetChildrenCount() == 0)
    {
        UTDTwoButtonHorizontalBox* horizontalTemp = NewObject<UTDTwoButtonHorizontalBox>(_verticalBox, UTDTwoButtonHorizontalBox::StaticClass(), TEXT("HorizontalBox"));

        _verticalBox->AddChildToVerticalBox(horizontalTemp);

        horizontalTemp->TDAddButton(_card);
    }
    else
    {
        int arraySize = _verticalBox->GetChildrenCount();

        UTDTwoButtonHorizontalBox* horizontalTemp = Cast<UTDTwoButtonHorizontalBox>(_verticalBox->GetChildAt(arraySize - 1));

        if (IsValid(horizontalTemp) && !horizontalTemp->TDAddButton(_card))
        {
            horizontalTemp = NewObject<UTDTwoButtonHorizontalBox>(_verticalBox, UTDTwoButtonHorizontalBox::StaticClass(), TEXT("HorizontalBox"));

            _verticalBox->AddChildToVerticalBox(horizontalTemp);

            horizontalTemp->TDAddButton(_card);
        }
    }


}

void UTDInventory::TDFillStructures()
{
    if (resourcesDataTable)
    {
        TArray<FName> rowNames = resourcesDataTable->GetRowNames();
        FTDResourceCardParameters* row;
        FString context = TEXT("DataTableContext");

        for (FName name : rowNames)
        {
            row = resourcesDataTable->FindRow<FTDResourceCardParameters>(name, context);
            UTDResourceCard* resourceCard = CreateWidget<UTDResourceCard>(this, *row->resourceClass);
            UTDResourceCard::TDSetResourceCardAttributes(*row, resourceCard);

            switch (row->column)
            {
            case ETDInventoryEnum::HeroBP:
            {
                TDAddResourceCard(resourceCard, heroBPs);
            }
            break;
            case ETDInventoryEnum::TowerBP:
            {
                TDAddResourceCard(resourceCard, towerBPs);
            }
            break;
            case ETDInventoryEnum::Gems:
            {
                TDAddResourceCard(resourceCard, gems);
            }
            break;
            default:
                break;
            }
        }
    }
}
