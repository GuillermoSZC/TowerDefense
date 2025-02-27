#include "Map/TDTowerStructure.h"
#include "Components/StaticMeshComponent.h"
#include "GameLogic/TDGameData.h"
#include "Character/TDPlayerCharacter.h"
#include "UI/TDTowerShop.h"
#include "GameLogic/TDRoundManager.h"
#include "TDTower.h"
#include <UMG/Public/Blueprint/WidgetBlueprintLibrary.h>
#include "Character/TDPlayerController.h"
#include "Components/TDWidgetShopComponent.h"
#include "GameLogic/TDCostManager.h"


FName ATDTowerStructure::StaticMeshName(TEXT("StructureMesh"));

ATDTowerStructure::ATDTowerStructure()
{
    PrimaryActorTick.bCanEverTick = true;

    towerStructure = CreateDefaultSubobject<UStaticMeshComponent>(ATDTowerStructure::StaticMeshName);

    widgetShopRef = CreateDefaultSubobject<UTDWidgetShopComponent>("TDWidgetShop");
    RootComponent = towerStructure;

    //isTowerSpawned = false;

    towerMap.Add(ETowers::Balistic, nullptr);
    towerMap.Add(ETowers::Sonic, nullptr);
    towerMap.Add(ETowers::DeathRay, nullptr);
    towerMap.Add(ETowers::Attack, nullptr);
    towerMap.Add(ETowers::Speed, nullptr);
}

void ATDTowerStructure::TDTriggerOpenUI()
{
    OnClicked.Broadcast(this,FKey());
}

void ATDTowerStructure::TDCalcultateCostWithLoot_Implementation(FBuyCost& _cost, ELootItems _item)
{
    _cost.BPItem = _item;
    UTDGameData::TDGetCostManager()->TDCalculateUpgradeCost(_cost, 1);
}

bool ATDTowerStructure::TDCanAffordCostWithLoot_Implementation(FBuyCost& _cost)
{
    return UTDGameData::TDGetCostManager()->TDCanAffordBuy(_cost);
}

bool ATDTowerStructure::TDCommitBuyUpgrade_Implementation(ELootItems _item)
{
    FBuyCost cost = FBuyCost();

    cost.BPItem = _item;

    ITDCostInterface::Execute_TDCalcultateCostWithLoot(this, cost, cost.BPItem);

    if (!ITDCostInterface::Execute_TDCanAffordCostWithLoot(this, cost))
    {
        return false;
    }

    UTDGameData::TDGetCostManager()->TDCommitResources(cost);
    return true;
}



void ATDTowerStructure::BeginPlay()
{
    Super::BeginPlay();

}


void ATDTowerStructure::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

void ATDTowerStructure::TDTowerSpawn(ETowers _tower)
{
    FVector location = GetActorLocation();

    GetWorld()->SpawnActor(towerMap[_tower], &location, &FRotator::ZeroRotator);

    //TDHideUI();

    /*isTowerSpawned = true;*/
}
