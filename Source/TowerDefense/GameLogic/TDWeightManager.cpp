// Fill out your copyright notice in the Description page of Project Settings.


#include "GameLogic/TDWeightManager.h"
#include "TDGameData.h"
#include "Map/TDSpawner.h"
#include "Character/TDEnemy.h"


UTDWeightManager* UTDWeightManager::weightManager = nullptr;



UTDWeightManager::UTDWeightManager()
{

}


UTDWeightManager* UTDWeightManager::TDGetWeightManager()
{


    if (weightManager == nullptr)
    {
        UWorld* actualWorld = UTDGameData::TDGetWorld();
        FActorSpawnParameters paramet;
        weightManager = actualWorld->SpawnActor<UTDWeightManager>();
    }

    return weightManager;

}



void UTDWeightManager::StartSpawn(TSubclassOf<ATDEnemy> _enemyClass)
{
    int actualWegith = 0;
    while (actualWegith < WeightPerRound)
    {
        UWorld* actualWorld = UTDGameData::TDGetWorld();

        ATDEnemy* actualEnemy = actualWorld->SpawnActor<ATDEnemy>(_enemyClass);

        actualWegith += actualEnemy->unitWeight;

        ATDSpawner* spawnerRef = UTDGameData::TDGetSpanwerActor();

        spawnerRef->TDSpawnEnemy(actualEnemy);

    }
}


