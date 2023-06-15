#include "UI/Utilities/TDRowStringList.h"
#include <UMG/Public/Components/ComboBoxString.h>

bool UTDRowStringList::Initialize()
{
    Super::Initialize();


    return true;
}

void UTDRowStringList::NativePreConstruct()
{
    Super::NativePreConstruct();

    if (stringList)
    {
        for (FString key : customOptions)
        {
            stringList->AddOption(key);
        }

        if (stringList->GetOptionCount() > 0)
        {
            stringList->SetSelectedOption(stringList->GetOptionAtIndex(0));
        }
    }
}

void UTDRowStringList::NativeConstruct()
{
    Super::NativeConstruct();


}
