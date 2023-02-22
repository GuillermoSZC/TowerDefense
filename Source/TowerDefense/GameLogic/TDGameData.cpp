// Fill out your copyright notice in the Description page of Project Settings.


#include "TDGameData.h"
#include "Engine/World.h"
#include "Gas/TDGameplayEventData.h"
#include "Character/TDEnemy.h"


UWorld* UTDGameData::gameWorld = nullptr;
UTDGameplayEventData* UTDGameData::abilityData = nullptr;
TArray<ATDEnemy*> UTDGameData::enemiesArray;


UTDGameData::UTDGameData(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}




void UTDGameData::TDResetGameData()
{
    gameWorld = nullptr;
    enemiesArray.Empty();
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





UTDGameplayEventData* const UTDGameData::TDGetAbilityStrcut()
{
    return abilityData;
}

void UTDGameData::TDSetAbilityStruct(UTDGameplayEventData* _NewAbilityData)
{
    abilityData = _NewAbilityData;
}
