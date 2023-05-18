// Fill out your copyright notice in the Description page of Project Settings.


#include "GameLogic/TDCostManager.h"

UTDCostManager::UTDCostManager()
{
    TowerBuyCost.Add(ETowers::Balistic, 1);
    TowerBuyCost.Add(ETowers::Sonic, 1);
    TowerBuyCost.Add(ETowers::DeathRay, 1);
    TowerBuyCost.Add(ETowers::Speed, 1);
    TowerBuyCost.Add(ETowers::Attack, 1);
}

int32 UTDCostManager::TDCalculateTowerBuyCost_Implementation(ETowers _tower)
{
    return 0;
}
