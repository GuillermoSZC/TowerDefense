#include "UI/TDUserWidget.h"

bool UTDUserWidget::Initialize()
{
    Super::Initialize();

    return false;
}

void UTDUserWidget::NativePreConstruct()
{
    Super::NativePreConstruct();


}

void UTDUserWidget::NativeConstruct()
{
    Super::NativeConstruct();


}

AActor* UTDUserWidget::TDGetOwner()
{
    return owner;
}

void UTDUserWidget::TDSetOwner(AActor* _owner)
{
    owner = _owner;
}
