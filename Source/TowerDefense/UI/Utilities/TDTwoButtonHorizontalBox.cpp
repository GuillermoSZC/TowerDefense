#include "UI/Utilities/TDTwoButtonHorizontalBox.h"
#include "TDComposedButton.h"
#include <UMG/Public/Blueprint/UserWidget.h>


bool UTDTwoButtonHorizontalBox::TDAddButton(UUserWidget* _component)
{
    if (IsValid(_component))
    {
        if (GetChildrenCount() < childCount)
        {
            AddChildToHorizontalBox(_component);

            return true;
        }
    }

    return false;
}