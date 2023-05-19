// Fill out your copyright notice in the Description page of Project Settings.


#include "TDGameData.h"
#include "Engine/World.h"
#include "Gas/TDGameplayEventData.h"
#include "Character/TDEnemy.h"
#include "Character/TDPlayerCharacter.h"
#include "TDObjectPooler.h"
#include "TDWeightManager.h"
#include "TDRoundManager.h"
#include "Map/TDTowerStructure.h"
#include "Map/TDTower.h"
#include "Map/TDBase.h"


UWorld* UTDGameData::gameWorld = nullptr;
UTDGameplayEventData* UTDGameData::abilityData = nullptr;
TArray<ATDEnemy*> UTDGameData::enemiesArray;
TArray<ATDSpawner*> UTDGameData::spawnerArray;
ATDBase* UTDGameData::baseRef = nullptr;
UTDWeightManager* UTDGameData::weightManagerRef = nullptr;
ATDGameMode* UTDGameData::GameModeRef = nullptr;
UTDGameInstance* UTDGameData::GameInstanceRef = nullptr;
ATDRoundManager* UTDGameData::RoundManagerRef = nullptr;
ATDObjectPooler* UTDGameData::ObjectPoolerRef = nullptr;
ATDPlayerCharacter* UTDGameData::playerRef = nullptr;
UTDCostManager* UTDGameData::CostManagerRef = nullptr;

UTDGameData::UTDGameData(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UTDGameData::TDResetGameData()
{
    gameWorld = nullptr;
    enemiesArray.Empty();
    abilityData = nullptr;
    baseRef = nullptr;
    spawnerArray.Empty();
    
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





void UTDGameData::TDRemoveEnmemyToArray(ATDEnemy* _ActualEnemy)
{
    if (enemiesArray.Contains(_ActualEnemy))
    {
        enemiesArray.Remove(_ActualEnemy);

        UTDGameData::TDGetRoundManager()->TDMinusEnemyKillCounter();
    }
}


void UTDGameData::TDDisableAllEnemies()
{
    for (ATDEnemy* iter : enemiesArray)
    {
        iter->TDSetDisable();
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

UTDGameplayEventData* UTDGameData::TDGetAbilityStruct()
{
    return abilityData;
}

ATDEnemy* UTDGameData::TDGetNearEnemyToBase()
{
    float minValue = FLT_MAX;
    ATDEnemy* nearEnemy = nullptr;


    for (ATDEnemy* it : enemiesArray)
    {
        float x = it->TDGetPathDistance();

        if (x < minValue)
        {
            minValue = x;
            nearEnemy = it;
        }
    }
    return nearEnemy;


}

ATDEnemy* UTDGameData::TDGetNearEnemyFromArrayToBase(TArray<AActor*> _enemies)
{

    float minValue = FLT_MAX;
    ATDEnemy* nearEnemy = nullptr;


    for (AActor* it : _enemies)
    {
        ATDEnemy* tempEnemy = Cast<ATDEnemy>(it);

        float x = tempEnemy->TDGetPathDistance();

        if (x < minValue)
        {
            minValue = x;
            nearEnemy = tempEnemy;
        }
    }
    return nearEnemy;



}

ATDBase* UTDGameData::TDGetBaseActor()
{
    return baseRef;
}

void UTDGameData::TDSetBaseActor(ATDBase* _baseRef)
{
    baseRef = _baseRef;
}



UTDWeightManager* UTDGameData::TDGetWeightManager()
{
    return weightManagerRef;
}

void UTDGameData::TDSetWeightManager(UTDWeightManager* _weightManagerRef)
{
    weightManagerRef = _weightManagerRef;
}

void UTDGameData::TDaddSpawnerActor(ATDSpawner* _spawnerRef)
{
    spawnerArray.Add(_spawnerRef);
}

ATDSpawner* UTDGameData::TDGetSpanwerActor()
{

    int x = FMath::Rand() % spawnerArray.Num();

    return spawnerArray[x];


}

ATDGameMode* UTDGameData::TDGetGameMode()
{
    return GameModeRef;
}

void UTDGameData::TDSetGameInstance(UTDGameInstance* _gameinmstanceRef)
{
    GameInstanceRef = _gameinmstanceRef;
}

UTDGameInstance* UTDGameData::TDGetGameInstance()
{
    return GameInstanceRef;
}

void UTDGameData::TDSetGameMode(ATDGameMode* _gameModeRef)
{
    GameModeRef = _gameModeRef;
}

void UTDGameData::TDSetRoundManager(ATDRoundManager* _RoundManagerRef)
{
    RoundManagerRef = _RoundManagerRef;
}

ATDRoundManager* UTDGameData::TDGetRoundManager()
{
    return RoundManagerRef;
}

void UTDGameData::TDSetObjectPooler(ATDObjectPooler* _ObjectPooler)
{
    ObjectPoolerRef = _ObjectPooler;
}

ATDObjectPooler* UTDGameData::TDGetObjectPooler()
{
    return ObjectPoolerRef;
}

ATDPlayerCharacter* UTDGameData::TDGetPlayerRef()
{
    return playerRef;
}

void UTDGameData::TDSetPlayerRef(ATDPlayerCharacter* _ref)
{
    playerRef = _ref;
}

UTDCostManager* UTDGameData::TDGetCostManager()
{
    return CostManagerRef;
}

void UTDGameData::TDSetCostManager(UTDCostManager* _ref)
{
    CostManagerRef = _ref;
}

FText UTDGameData::TDConvertIntToFText(int32 _num)
{
    FString StringTemp = FString::FromInt(_num);
    FText texttemp = FText::FromString(StringTemp);
    return texttemp;
}

void UTDGameData::TDSpawnEnemyDebug()
{
    weightManagerRef->TDSpawnEnemy();
}

