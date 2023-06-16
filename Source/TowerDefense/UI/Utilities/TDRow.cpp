#include "UI/Utilities/TDRow.h"
#include <UMG/Public/Components/Spacer.h>
#include "TDRichTextBlock.h"
#include <UMG/Public/Components/SizeBox.h>


bool UTDRow::Initialize()
{
    Super::Initialize();

    return true;
}

void UTDRow::NativePreConstruct()
{
    Super::NativePreConstruct();

    TDSetText(rowText);
}

void UTDRow::NativeConstruct()
{
    Super::NativeConstruct();

}

void UTDRow::TDSetText(FText _text)
{
    rowText = _text;

    if (richText)
    {
        richText->SetText(rowText);
    }
}
