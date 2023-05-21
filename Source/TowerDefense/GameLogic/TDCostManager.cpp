// Fill out your copyright notice in the Description page of Project Settings.


#include "GameLogic/TDCostManager.h"

ATDCostManager::ATDCostManager()
{
    TowerBuyCost.Add(ETowers::Balistic, FBuyCost());
    TowerBuyCost.Add(ETowers::Sonic, FBuyCost());
    TowerBuyCost.Add(ETowers::DeathRay, FBuyCost());
    TowerBuyCost.Add(ETowers::Speed, FBuyCost());
    TowerBuyCost.Add(ETowers::Attack, FBuyCost());
}

FBuyCost ATDCostManager::TDCalculateTowerBuyCost_Implementation(ELootItems _Item)
{
    return FBuyCost();
}

bool ATDCostManager::TDCanAffordBuy(ELootItems _BPItem)
{
    FBuyCost costTemp = TDCalculateTowerBuyCost_Implementation(_BPItem);

    TMap<ELootItems, int32> PlayerInventory;

    PlayerInventory = UTDGameData::TDGetPlayerRef()->TDGetPlayerInventory();

    int32 PlayerScrap = PlayerInventory[ELootItems::Scrap];
    int32 PlayerBP = PlayerInventory[_BPItem];


    if (PlayerScrap >= costTemp.scrapCost && PlayerBP >= costTemp.BPCost)
    {
        return true;
    }

    return false;
}

