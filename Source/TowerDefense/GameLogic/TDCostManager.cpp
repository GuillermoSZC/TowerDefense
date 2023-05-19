// Fill out your copyright notice in the Description page of Project Settings.


#include "GameLogic/TDCostManager.h"

UTDCostManager::UTDCostManager()
{
    TowerBuyCost.Add(ETowers::Balistic, FBuyCost());
    TowerBuyCost.Add(ETowers::Sonic, FBuyCost());
    TowerBuyCost.Add(ETowers::DeathRay, FBuyCost());
    TowerBuyCost.Add(ETowers::Speed, FBuyCost());
    TowerBuyCost.Add(ETowers::Attack, FBuyCost());
}

FBuyCost UTDCostManager::TDCalculateTowerBuyCost_Implementation(ETowers _tower)
{
    return FBuyCost();
}
