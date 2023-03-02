// Fill out your copyright notice in the Description page of Project Settings.


#include "TDGameMode.h"
#include "TDGameData.h"
#include "TDObjectPooler.h"
#include "Gas/TDGameplayEventData.h"
#include "TDWeightManager.h"
#include "Engine/DataTable.h"


ATDGameMode::ATDGameMode()
{
    UTDGameData::TDResetGameData();
}

void ATDGameMode::StartPlay()
{
    Super::StartPlay();
  


    UWorld* world = GetWorld();
    UTDGameData::TDSetWorld(world);

    UTDGameData::TDSetAbilityStruct(NewObject<UTDGameplayEventData>(UTDGameplayEventData::StaticClass()));
    ATDObjectPooler* objectPooler = ATDObjectPooler::TDGetObjectPooler(objectPoolerClass);

    UTDWeightManager* weightManager = UTDWeightManager::TDGetWeightManager();
    UTDGameData::TDSetWeightManager(weightManager);
    weightManager->TDSetDataTable(statsDatatable);
    //weightManager->TDStartSpawn(EnemyClass);
    

}

void ATDGameMode::StartToLeaveMap()
{
    Super::StartToLeaveMap();

    UTDGameData::TDResetGameData();

}

void ATDGameMode::Reset()
{
    Super::Reset();

}
