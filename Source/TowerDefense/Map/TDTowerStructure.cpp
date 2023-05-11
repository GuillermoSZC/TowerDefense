#include "Map/TDTowerStructure.h"
#include "Components/StaticMeshComponent.h"
#include "GameLogic/TDGameData.h"
#include "Character/TDPlayerCharacter.h"
#include "UI/TDTowerShop.h"
#include "GameLogic/TDRoundManager.h"
#include "TDTower.h"
#include <UMG/Public/Blueprint/WidgetBlueprintLibrary.h>
#include "Character/TDPlayerController.h"


FName ATDTowerStructure::StaticMeshName(TEXT("StructureMesh"));
UTDTowerShop* ATDTowerStructure::uiShopRef = nullptr;

ATDTowerStructure::ATDTowerStructure()
{
    PrimaryActorTick.bCanEverTick = true;

    towerStructure = CreateDefaultSubobject<UStaticMeshComponent>(ATDTowerStructure::StaticMeshName);

    RootComponent = towerStructure;

    isUIActive = false;
    isTowerSpawned = false;

    towerMap.Add(ETowers::Balistic, nullptr);
    towerMap.Add(ETowers::Sonic, nullptr);
    towerMap.Add(ETowers::DeathRay, nullptr);
    towerMap.Add(ETowers::Attack, nullptr);
    towerMap.Add(ETowers::Speed, nullptr);
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
    if (isTowerSpawned)
    {
        return false;
    }

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
        uiShopRef->TDSetOwner(nullptr);
        UWidgetBlueprintLibrary::SetInputMode_GameOnly(Cast<ATDPlayerController>(UTDGameData::playerRef->GetController()));
    }
}

void ATDTowerStructure::TDVisibleUI_Implementation()
{
    isUIActive = true;

    if (uiShopRef)
    {
        uiShopRef->SetVisibility(ESlateVisibility::Visible);
        uiShopRef->TDSetOwner(this);
        UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(Cast<ATDPlayerController>(UTDGameData::playerRef->GetController()), uiShopRef);
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

void ATDTowerStructure::TDTowerSpawn(ETowers _tower)
{
    FVector location = GetActorLocation();

    GetWorld()->SpawnActor(towerMap[_tower], &location, &FRotator::ZeroRotator);

    TDHideUI();
    
    isTowerSpawned = true;
}
