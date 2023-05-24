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

ATDTowerStructure::ATDTowerStructure()
{
    PrimaryActorTick.bCanEverTick = true;

    towerStructure = CreateDefaultSubobject<UStaticMeshComponent>(ATDTowerStructure::StaticMeshName);

    RootComponent = towerStructure;

    //isTowerSpawned = false;

    towerMap.Add(ETowers::Balistic, nullptr);
    towerMap.Add(ETowers::Sonic, nullptr);
    towerMap.Add(ETowers::DeathRay, nullptr);
    towerMap.Add(ETowers::Attack, nullptr);
    towerMap.Add(ETowers::Speed, nullptr);
}

void ATDTowerStructure::TDCalcultateCost_Implementation(FBuyCost& _cost, ELootItems _item)
{
       UTDGameData::TDGetCostManager()->TDCalculateTowerBuyCost(_cost,_item);       
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
