#include "UI/Utilities/TDRow.h"
#include <UMG/Public/Components/Spacer.h>

bool UTDRow::Initialize()
{
    Super::Initialize();

    return true;
}

void UTDRow::NativePreConstruct()
{
    Super::NativePreConstruct();

    if (customSpacer)
    {
        customSpacer->SetSize(spacerSize);
    }
}

void UTDRow::NativeConstruct()
{
    Super::NativeConstruct();

}
