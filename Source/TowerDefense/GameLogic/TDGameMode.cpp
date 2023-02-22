// Fill out your copyright notice in the Description page of Project Settings.


#include "TDGameMode.h"
#include "TDGameData.h"
#include "TDObjectPooler.h"
#include "Gas/TDGameplayEventData.h"

void ATDGameMode::StartPlay()
{
    Super::StartPlay();
  

    UWorld* world = GetWorld();
    UTDGameData::TDSetWorld(world);

    UTDGameData::TDSetAbilityStruct(NewObject<UTDGameplayEventData>(UTDGameplayEventData::StaticClass()));

   ATDObjectPooler* objectPooler = ATDObjectPooler::TDGetObjectPooler();

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
