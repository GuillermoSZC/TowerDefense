#include "UI/Utilities/TDTwoButtonHorizontalBox.h"
#include "TDComposedButton.h"
#include <UMG/Public/Blueprint/UserWidget.h>


void UTDTwoButtonHorizontalBox::TDAddButton(UUserWidget* _button)
{
    if (IsValid(_button))
    {
        if (GetChildrenCount() < childCount)
        {
            AddChild(_button);
        }
    }
}