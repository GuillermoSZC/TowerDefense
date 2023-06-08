// Fill out your copyright notice in the Description page of Project Settings.


#include "TDGameInstance.h"

UTDGameInstance::UTDGameInstance()
{

}

void UTDGameInstance::TDOpenMap(UObject* _world)
{
    UGameplayStatics::OpenLevelBySoftObjectPtr(_world, worldRef, true);
}
