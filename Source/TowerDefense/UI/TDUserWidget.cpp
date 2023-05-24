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


    OnVisibilityChanged.AddDynamic(this, &UTDUserWidget::TDOnVisibilityChange);
    FUICostUpdateDelegate.AddDynamic(this, &UTDUserWidget::TDUpdateCost);
        
}

UTDWidgetShopComponent* UTDUserWidget::TDGetOwner()
{
    return owner;
}

void UTDUserWidget::TDSetOwner(UTDWidgetShopComponent* _owner)
{
    owner = _owner;
}

void UTDUserWidget::TDOnVisibilityChange(ESlateVisibility _visible)
{

}

void UTDUserWidget::TDUpdateCost()
{

}
