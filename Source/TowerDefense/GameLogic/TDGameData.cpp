// Fill out your copyright notice in the Description page of Project Settings.


#include "TDGameData.h"

UWorld* UTDGameData::gameWorld = nullptr;

UWorld* UTDGameData::TDGetWorld()
{
    return gameWorld;
}

void UTDGameData::TDSetWorld(UWorld* _ActualMap)
{
    gameWorld = _ActualMap;
}
