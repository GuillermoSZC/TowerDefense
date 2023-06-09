#include "UI/MainMenu/TDLevelSelector.h"
#include <Kismet/GameplayStatics.h>
#include "GameLogic/Structs/TDLevelSelectorButtons.h"
#include <Engine/DataTable.h>
#include "UI/Utilities/TDRichTextBlock.h"
#include "UI/Utilities/TDButtonMap.h"
#include <UMG/Public/Components/VerticalBox.h>


bool UTDLevelSelector::Initialize()
{
    Super::Initialize();

    return true;
}

void UTDLevelSelector::NativePreConstruct()
{
    Super::NativePreConstruct();

    if (buttonsContainer->GetChildrenCount() == 0)
    {
        TDInitButtons();
    }
}

void UTDLevelSelector::NativeConstruct()
{
    Super::NativeConstruct();

}

void UTDLevelSelector::TDInitButtons()
{
    if (buttonsDataTable)
    {
        TArray<FName> rowNames = buttonsDataTable->GetRowNames();
        FTDLevelSelectorButtons* row;
        FString context = TEXT("DataTableContext");

        for (FName name : rowNames)
        {
            row = buttonsDataTable->FindRow<FTDLevelSelectorButtons>(name, context);
            UTDButtonMap* tempButton = nullptr;
            //tempButton = NewObject<UTDButtonMap>(buttonsContainer, *row->buttonClass);
            tempButton = CreateWidget<UTDButtonMap>(this, *row->buttonClass);

            tempButton->TDSetFont(row->fonts);
            tempButton->TDSetText(row->buttonName);
            tempButton->TDSetPadding(row->padding);
            tempButton->TDSetLevelReference(row->levelReference);
            tempButton->TDSetIsInfinite(row->isInfinite);

            if (row->bCanModify)
            {
                tempButton->TDSetButtonStyle(row->buttonStyle);
            }

            buttonsContainer->AddChildToVerticalBox(tempButton);
        }
    }
}