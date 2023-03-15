 // Fill out your copyright notice in the Description page of Project Settings.


#include "GameLogic/TDRoundManager.h"
#include "TDRoundElementsType.h"





ATDRoundManager::ATDRoundManager()
{
    PrimaryActorTick.bCanEverTick = true;
}

ATDRoundManager::~ATDRoundManager()
{
   
}






void ATDRoundManager::BeginPlay()
{
    Super::BeginPlay();

    TDStartBuyPhase();
}

void ATDRoundManager::TDStartBuyPhase()
{
    timeRound = timeBuyPhase;
    actualPhase = GamePhase::BuyPhase;
    FOnBuyPhaseStartDelegate.Broadcast(actualRound);
}

void ATDRoundManager::TDStartCombatPhase()
{
    TDStartRound();
    FOnCombatPhaseStartDelegate.Broadcast(actualRound);
}

void ATDRoundManager::TDStartRound()
{

    actualPhase = GamePhase::CombatPhase;
    ++actualRound;
    isSawning = true;
    timeRound = timeperSpawn;

    actualRoundElements.Empty();

    int x;

    if (actualRound >= RoundElements.Num())
    {
         x = actualRound % RoundElements.Num();
    }
    else
    {
        x = actualRound - 1;
    }

    RoundElements[x]->TDGetRoundElements(actualRoundElements);

   
    RoundWeight = UTDGameData::TDGetWeightManager()->TDSetActualRound(actualRound, actualRoundElements);
    killedWegith = 0;
}

void ATDRoundManager::TDStopRound()
{
    isSawning = false;
}


void ATDRoundManager::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);


    if (actualPhase == GamePhase::CombatPhase && isSawning)
    {
        if (timeRound >= timeperSpawn)
        {

            UTDGameData::TDGetWeightManager()->TDStartSpawn();


            timeRound -= timeperSpawn;
        }

        timeRound += DeltaSeconds;
    }

    if (actualPhase == GamePhase::BuyPhase)
    {

        if (timeRound <= 0.f)
        {

            TDStartCombatPhase();

        }    

        GEngine->AddOnScreenDebugMessage(0, 0.f, FColor::Blue, FString::SanitizeFloat(timeRound));
        timeRound -= DeltaSeconds;

    }


}

void ATDRoundManager::TDEnemyKillWeight(int32& _weight)
{

    killedWegith += _weight;

    if (killedWegith >= RoundWeight)
    {

        GEngine->AddOnScreenDebugMessage(0,5.f,FColor::Yellow,"Todos muertos");

        TDStartBuyPhase();

    }

}

float ATDRoundManager::TDGetTimeRound()
{
    return timeRound;
}
