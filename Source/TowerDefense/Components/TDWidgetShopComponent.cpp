#include "Components/TDWidgetShopComponent.h"
#include "GameLogic/TDGameData.h"
#include <UMG/Public/Blueprint/WidgetBlueprintLibrary.h>

UTDWidgetShopComponent::UTDWidgetShopComponent()
{

    PrimaryComponentTick.bCanEverTick = true;

    isUIActive = false;
    distanceToUI = 1000.f;
}

void UTDWidgetShopComponent::BeginPlay()
{
    Super::BeginPlay();

    distSquared = distanceToUI * distanceToUI;

    // GetOwner()->OnClicked.AddDynamic(this, &UTDWidgetShopComponent::TDOnClickedActor);
}

void UTDWidgetShopComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UTDWidgetShopComponent::TDHideUI_Implementation()
{
//     isUIActive = false;
// 
//     if (widgetRef)
//     {
//         widgetRef->SetVisibility(ESlateVisibility::Collapsed);
//         UWidgetBlueprintLibrary::SetInputMode_GameOnly(Cast<ATDPlayerController>(UTDGameData::playerRef->GetController()));
//     }
}

void UTDWidgetShopComponent::TDVisibleUI_Implementation()
{
//     isUIActive = true;
// 
//     if (widgetRef)
//     {
//         widgetRef->TDSetOwner(this);
//         widgetRef->SetVisibility(ESlateVisibility::Visible);
//         UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(Cast<ATDPlayerController>(UTDGameData::playerRef->GetController()), widgetRef);
//     }
}

void UTDWidgetShopComponent::TDOnClickedActor_Implementation(AActor* Target, FKey ButtonPressed)
{

}

float UTDWidgetShopComponent::TDCheckDistanceWithPlayer()
{
    return 0.f;
}

bool UTDWidgetShopComponent::TDCheckPlayerInRange()
{
    return false;
}

bool UTDWidgetShopComponent::TDCanShowUI()
{
    return false;
}

void UTDWidgetShopComponent::TDOnBuyPhaseStart(int32 _value)
{
    if (isUIActive)
    {
        TDHideUI();
    }
}
