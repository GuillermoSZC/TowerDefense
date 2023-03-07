// Fill out your copyright notice in the Description page of Project Settings.


#include "GameLogic/TDRoundManager.h"





ATDRoundManager::ATDRoundManager()
{
    PrimaryActorTick.bCanEverTick = true;
}

ATDRoundManager::~ATDRoundManager()
{
    managerRef = nullptr;
}



ATDRoundManager* ATDRoundManager::managerRef = nullptr;


void ATDRoundManager::BeginPlay()
{
    Super::BeginPlay();


}

void ATDRoundManager::TDStartRound()
{
    ++actualRound;
    isSawning = true;
    timeRound = timeperSpawn;
    RoundWeight= UTDWeightManager::TDGetWeightManager()->TDSetActualRound(actualRound);
    killedWegith = 0;
}

void ATDRoundManager::TDStopRound()
{
    isSawning = false;
}

ATDRoundManager* ATDRoundManager::TDGetRoundManager()
{

    if (managerRef == nullptr)
    {
        UWorld* actualWorld = UTDGameData::TDGetWorld();
        FActorSpawnParameters paramet;
        //OwnerPooler = Cast<ATDObjectPooler>(actualWorld->SpawnActor(ATDObjectPooler::StaticClass()));
        managerRef = actualWorld->SpawnActor<ATDRoundManager>();
    }
    return managerRef;
}

void ATDRoundManager::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);


    if (isSawning)
    {
        if (timeRound >= timeperSpawn)
        {

            UTDWeightManager::TDGetWeightManager()->TDStartSpawn();


            timeRound -= timeperSpawn;
        }

        timeRound += DeltaSeconds;
    }

    


}

void ATDRoundManager::TDEnemyKillWeight(int32& _weight)
{

    killedWegith += _weight;

    if (killedWegith >= RoundWeight)
    {

        GEngine->AddOnScreenDebugMessage(0,5.f,FColor::Yellow,"Todos muertos");

    }

}
