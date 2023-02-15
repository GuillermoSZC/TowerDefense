// Fill out your copyright notice in the Description page of Project Settings.


#include "TDGameData.h"

UWorld* UTDGameData::gameWorld = nullptr;
UTDGameplayEventData* UTDGameData::abilityData = nullptr;
TArray<ATDEnemy*> UTDGameData::enemiesArray;

void UTDGameData::TDResetGameData()
{
    gameWorld = nullptr;
    enemiesArray.Empty();
    abilityData->BeginDestroy();
    abilityData = nullptr;
}

UWorld* UTDGameData::TDGetWorld()
{
    return gameWorld;
}

void UTDGameData::TDSetWorld(UWorld* _ActualMap)
{
    gameWorld = _ActualMap;
}

TArray<ATDEnemy*> UTDGameData::TDGetEnemiesArray()
{
    return enemiesArray;
}

void UTDGameData::TDAddEnmemyToArray(ATDEnemy* _ActualEnemy)
{
    if (!enemiesArray.Contains(_ActualEnemy))
    {
        enemiesArray.Add(_ActualEnemy);
    }
}

UTDGameplayEventData* UTDGameData::TDGetAbilityStrcut()
{
    return abilityData;
}

void UTDGameData::TDSetAbilityStruct(UTDGameplayEventData* _NewAbilityData)
{
    abilityData = _NewAbilityData;
}
