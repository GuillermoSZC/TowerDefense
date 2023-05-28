#include "UI/Utilities/TDTwoButtonHorizontalBox.h"
#include "TDComposedButton.h"


void UTDTwoButtonHorizontalBox::TDAddButton(UTDComposedButton* _button)
{
    if (IsValid(_button))
    {
        if (GetChildrenCount() < childCount)
        {
            AddChild(_button);
        }
    }
}