// Fill out your copyright notice in the Description page of Project Settings.


#include "GameLogic/TDCostManager.h"

ATDCostManager::ATDCostManager()
{
    TowerBuyCost.Add(ELootItems::BalisticBP, FBuyCost());
    TowerBuyCost.Add(ELootItems::SonicBP, FBuyCost());
    TowerBuyCost.Add(ELootItems::DeathRayBP, FBuyCost());
    TowerBuyCost.Add(ELootItems::SpeedTowerBP, FBuyCost());
    TowerBuyCost.Add(ELootItems::AttackTowerBP, FBuyCost());
}

// void ATDCostManager::TDCalculateTowerBuyCost_Implementation(FBuyCost& _cost)
// {
// 
//     _cost = TowerBuyCost[_cost.BPItem];
// }


void ATDCostManager::TDCalculateUpgradeCost_Implementation(FBuyCost& _cost, int32 _actualLevel)
{


    if (_cost.BPItem == ELootItems::Plasma || _cost.BPItem == ELootItems::Ice || _cost.BPItem == ELootItems::Fire || _cost.BPItem == ELootItems::None)
    {
        _cost = FBuyCost();
        return;
    }

    _cost.scrapCost = 3 + (_actualLevel - 1);
    _cost.BPCost = 1 + ((_actualLevel - 1) / 10);


}



void ATDCostManager::TDCommitResources(FBuyCost& _cost)
{
    TMap<ELootItems, int32> PlayerInventory;
    ATDPlayerCharacter* playerRef = UTDGameData::TDGetPlayerRef();
    PlayerInventory = playerRef->TDGetPlayerInventory();

    if (_cost.BPItem != ELootItems::None && _cost.GemItem == ELootItems::None)
    {
        int32 newScrap = PlayerInventory[ELootItems::Scrap] - _cost.scrapCost;
        int32 newBP = PlayerInventory[_cost.BPItem] - _cost.BPCost;

        playerRef->TDOverrideItemInInventory(ELootItems::Scrap, newScrap);
        playerRef->TDOverrideItemInInventory(_cost.BPItem, newBP);
    }

    if (_cost.BPItem == ELootItems::None && _cost.GemItem != ELootItems::None)
    {
        int32 newGems = PlayerInventory[_cost.GemItem] - _cost.GemCost;
        playerRef->TDOverrideItemInInventory(_cost.GemItem, newGems);
    }
    

}

bool ATDCostManager::TDCanAffordBuy(FBuyCost& _cost)
{  
    TMap<ELootItems, int32> PlayerInventory;
    PlayerInventory = UTDGameData::TDGetPlayerRef()->TDGetPlayerInventory();

    if (_cost.BPItem != ELootItems::None && _cost.GemItem == ELootItems::None)
    {
        int32 PlayerScrap = PlayerInventory[ELootItems::Scrap];
        int32 PlayerBP = PlayerInventory[_cost.BPItem];


        if (PlayerScrap >= _cost.scrapCost && PlayerBP >= _cost.BPCost)
        {
            return true;
        }
    }

    if (_cost.BPItem == ELootItems::None && _cost.GemItem != ELootItems::None && _cost.GemCost != 0)
    {
        int32 PlayerGem = PlayerInventory[_cost.GemItem];

        if (PlayerGem >= _cost.GemCost)
        {
            return true;
        }
    }   

    return false;
}

// bool ATDCostManager::TDCanAffordElementChange(FBuyCost& _cost, ELootItems _Item)
// {
// 
//     if (_cost.GemCost == 0)
//     {
//         return false;
//     }
// 
//     int32 gemNumber = UTDGameData::TDGetPlayerRef()->TDGetAmountItemByItem(_Item);
// 
//     if (gemNumber >= _cost.GemCost)
//     {
//         return true;
//     }
// 
// 
//     return false;
// }


void ATDCostManager::TDCalculateElementChange_Implementation(FBuyCost& _cost, EElements _Element, EElements _actualElement)
{

    if (_Element == _actualElement)
    {   
        return;
    }

    _cost.GemCost = 1;
}

