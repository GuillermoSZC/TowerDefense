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

    elementsDataAssets.Empty();

    elementsDataAssets.Add(EElements::None, nullptr);
    elementsDataAssets.Add(EElements::Fire, nullptr);
    elementsDataAssets.Add(EElements::Freeze, nullptr);
    elementsDataAssets.Add(EElements::Plasma, nullptr);

}


void ATDGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
    
    Super::InitGame(MapName, Options, ErrorMessage);

    UTDGameData::TDSetGameMode(this);

    UTDGameInstance* gameInstanceRef = Cast<UTDGameInstance>(GetGameInstance());
    UTDGameData::TDSetGameInstance(gameInstanceRef);


    UWorld* world = GetWorld();
    UTDGameData::TDSetWorld(world);

    UTDGameData::TDSetAbilityStruct(NewObject<UTDGameplayEventData>(UTDGameplayEventData::StaticClass()));

    ObjectPoolerRef = world->SpawnActor<ATDObjectPooler>(objectPoolerClass);
    UTDGameData::TDSetObjectPooler(ObjectPoolerRef);


    RoundManagerRef = world->SpawnActor<ATDRoundManager>(RoundManagerClass);
    UTDGameData::TDSetRoundManager(RoundManagerRef);

    weightManagerRef = NewObject<UTDWeightManager>(UTDWeightManager::StaticClass(), FName(TEXT("WeightManager")), EObjectFlags::RF_MarkAsRootSet);
    UTDGameData::TDSetWeightManager(weightManagerRef);
    weightManagerRef->TDSetDataTable(statsDatatable);


}


UTDElement* ATDGameMode::TDGetDataAssetFromElement(EElements _keyElement)
{
    return elementsDataAssets[_keyElement];
}

void ATDGameMode::StartPlay()
{
    Super::StartPlay();

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
