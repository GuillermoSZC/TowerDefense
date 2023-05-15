#include "Components/TDWidgetShopComponent.h"
#include "GameLogic/TDGameData.h"
#include <UMG/Public/Blueprint/WidgetBlueprintLibrary.h>
#include "GameLogic/TDGameMode.h"

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

    GetOwner()->OnClicked.AddDynamic(this, &UTDWidgetShopComponent::TDOnClickedActor);

    UTDGameData::TDGetRoundManager()->FOnBuyPhaseStartDelegate.AddDynamic(this, &UTDWidgetShopComponent::TDOnBuyPhaseStart);

    ATDPlayerController* playerController = UTDGameData::TDGetPlayerRef()->GetController<ATDPlayerController>();

    FOnOpenUIDelegate.AddDynamic(playerController, &ATDPlayerController::TDOnOpenUI);
    FOnCloseUIDelegate.AddDynamic(playerController, &ATDPlayerController::TDOnCloseUI);


    widgetRef = UTDGameData::TDGetGameMode()->TDGetWidgetFromClass(widgetClass);
}

void UTDWidgetShopComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


    if (isUIActive && !TDCheckPlayerInRange())
    {
        TDHideUI();
    }

}

void UTDWidgetShopComponent::TDHideUI_Implementation()
{
    isUIActive = false;

    if (widgetRef)
    {
        widgetRef->SetVisibility(ESlateVisibility::Collapsed);
        FOnCloseUIDelegate.Broadcast();
    }
}

void UTDWidgetShopComponent::TDVisibleUI_Implementation()
{
    isUIActive = true;

    if (widgetRef)
    {
        widgetRef->TDSetOwner(this);
        widgetRef->SetVisibility(ESlateVisibility::Visible);
        FOnOpenUIDelegate.Broadcast(widgetRef);
    }
}

void UTDWidgetShopComponent::TDOnClickedActor_Implementation(AActor* Target, FKey ButtonPressed)
{
    if (TDCanShowUI())
    {
        TDVisibleUI();
    }
}

float UTDWidgetShopComponent::TDCheckDistanceWithPlayer()
{
    float distanceSquared;

    FVector ownerLocation = GetOwner()->GetActorLocation();
    FVector playerLocation = UTDGameData::TDGetPlayerRef()->GetActorLocation();
    distanceSquared = FVector::DistSquared2D(ownerLocation, playerLocation);

    return distanceSquared;
}

bool UTDWidgetShopComponent::TDCheckPlayerInRange()
{
    if (TDCheckDistanceWithPlayer() > distSquared)
    {
        return false;
    }

    return true;
}

bool UTDWidgetShopComponent::TDCanShowUI()
{
    if (!TDCheckPlayerInRange())
    {
        return false;
    }

    if (UTDGameData::TDGetRoundManager()->TDGetActualPhase() != GamePhase::BuyPhase)
    {
        return false;
    }

    return true;
}

void UTDWidgetShopComponent::TDOnBuyPhaseStart(int32 _value)
{
    if (isUIActive)
    {
        TDHideUI();
    }
}
