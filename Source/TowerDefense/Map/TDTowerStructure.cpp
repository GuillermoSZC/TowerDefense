#include "Map/TDTowerStructure.h"
#include "Components/StaticMeshComponent.h"
#include "GameLogic/TDGameData.h"
#include "Character/TDPlayerCharacter.h"
#include "UI/TDTowerShop.h"
#include "GameLogic/TDRoundManager.h"


FName ATDTowerStructure::StaticMeshName(TEXT("StructureMesh"));
UTDTowerShop* ATDTowerStructure::uiShopRef = nullptr;

ATDTowerStructure::ATDTowerStructure()
{
    PrimaryActorTick.bCanEverTick = true;

    towerStructure = CreateDefaultSubobject<UStaticMeshComponent>(ATDTowerStructure::StaticMeshName);

    RootComponent = towerStructure;

    isUIActive = false;
}

void ATDTowerStructure::BeginPlay()
{
    Super::BeginPlay();

    OnClicked.AddDynamic(this, &ATDTowerStructure::TDOnClickedStructure);

    distSquared = distanceToUI * distanceToUI;

    if (uiShopClass && !uiShopRef)
    {
        uiShopRef = CreateWidget<UTDTowerShop>(GetWorld(), uiShopClass);
        uiShopRef->AddToViewport();
        uiShopRef->SetVisibility(ESlateVisibility::Collapsed);
    }

    UTDGameData::TDGetRoundManager()->FOnCombatPhaseStartDelegate.AddUniqueDynamic(this, &ATDTowerStructure::TDOnBuyPhaseStart);
}

float ATDTowerStructure::TDCheckDistanceWithPlayer()
{
    float distanceSquared;

    FVector ownerLocation = GetActorLocation();
    FVector playerLocation = UTDGameData::TDGetPlayerRef()->GetActorLocation();

    distanceSquared = FVector::DistSquared2D(ownerLocation, playerLocation);

    return distanceSquared;
}

bool ATDTowerStructure::TDCheckPlayerInRange()
{
    if (TDCheckDistanceWithPlayer() > distSquared)
    {
        return false;
    }

    return true;
}

bool ATDTowerStructure::TDCanShowUI()
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

void ATDTowerStructure::TDOnBuyPhaseStart(int _value)
{
    TDHideUI();
}

void ATDTowerStructure::TDHideUI_Implementation()
{
    isUIActive = false;

    if (uiShopRef)
    {
        uiShopRef->SetVisibility(ESlateVisibility::Collapsed);
    }
}

void ATDTowerStructure::TDVisibleUI_Implementation()
{
    isUIActive = true;

    if (uiShopRef)
    {
        uiShopRef->SetVisibility(ESlateVisibility::Visible);
    }
}

void ATDTowerStructure::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (isUIActive && !TDCheckPlayerInRange())
    {
        TDHideUI();
    }
}

