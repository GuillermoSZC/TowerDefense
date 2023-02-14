// Fill out your copyright notice in the Description page of Project Settings.


#include "TDGameMode.h"
#include "TDGameData.h"
#include "TDObjectPooler.h"

void ATDGameMode::StartPlay()
{
    Super::StartPlay();
  

    UWorld* world = GetWorld();
    UTDGameData::TDSetWorld(world);

   ATDObjectPooler* punteroprueba = ATDObjectPooler::TDGetObjectPooler();

}
