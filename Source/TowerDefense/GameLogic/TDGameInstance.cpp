// Fill out your copyright notice in the Description page of Project Settings.


#include "TDGameInstance.h"

UTDGameInstance::UTDGameInstance()
    : isInfiniteMap(false)
{

}

void UTDGameInstance::Init()
{
    Super::Init();
    
    UTDGameData::TDSetGameInstance(this);
    
}

void UTDGameInstance::TDOpenMap(UObject* _world)
{
    UGameplayStatics::OpenLevelBySoftObjectPtr(_world, worldRef, true);
}
