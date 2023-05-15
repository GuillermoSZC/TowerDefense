#include "UI/TDUserWidget.h"
#include "Components/TDWidgetShopComponent.h"


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

UTDWidgetShopComponent* UTDUserWidget::TDGetOwner()
{
    return owner;
}

void UTDUserWidget::TDSetOwner(UTDWidgetShopComponent* _owner)
{
    owner = _owner;
}
