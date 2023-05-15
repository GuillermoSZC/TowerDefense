// Fill out your copyright notice in the Description page of Project Settings.


#include "GameLogic/TDRoundManager.h"
#include "TDRoundElementsType.h"
#include "TDWeightManager.h"
#include "TDGameData.h"
#include "TDObjectPooler.h"
#include "Character/TDEnemyController.h"
#include "Character/TDEnemy.h"
#include <AIModule/Classes/BehaviorTree/BlackboardComponent.h>
#include "TDPathPoint.h"





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
}

void ATDRoundManager::TDPostBeginPlay()
{
    TDStartBuyPhase();
}

void ATDRoundManager::TDStartBuyPhase()
{
    timeRound = timeBuyPhase;
    actualPhase = GamePhase::BuyPhase;
    TDPrepareCombatRound();

    FOnBuyPhaseStartDelegate.Broadcast(actualRound);
}

void ATDRoundManager::TDStartCombatPhase()
{
    actualPhase = GamePhase::CombatPhase;
    timeRound = timeperSpawn;

    FOnCombatPhaseStartDelegate.Broadcast(actualRound);
}


void ATDRoundManager::TDPrepareCombatRound()
{
    ++actualRound;


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
    FOnElementSelectionDelegate.Broadcast(actualRoundElements);

    EnemiesToKill = UTDGameData::TDGetWeightManager()->TDSetActualRound(actualRound, actualRoundElements);
    FOnEnemyKillDelegate.Broadcast(EnemiesToKill);
}



void ATDRoundManager::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    if (actualPhase == GamePhase::CombatPhase )
    {
        if (timeRound >= timeperSpawn)
        {

            UTDGameData::TDGetWeightManager()->TDSpawnEnemy();
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
        timeRound -= DeltaSeconds;
    }
}

void ATDRoundManager::TDMinusEnemyKillCounter()
{
    --EnemiesToKill;

    FOnEnemyKillDelegate.Broadcast(EnemiesToKill);

    if (EnemiesToKill <= 0)
    {
        TDStartBuyPhase();
    }
}

void ATDRoundManager::TDAddEnemyKilCounter()
{
    EnemiesToKill += 1;
}

float ATDRoundManager::TDGetTimeRound()
{
    return timeRound;
}

int32 ATDRoundManager::TDGetActualRound()
{
    return actualRound;
}

ATDEnemy* ATDRoundManager::TDCreateEnemy(FName enemyName, AActor* _instigator)
{
    ATDObjectPooler* objectRef = UTDGameData::TDGetObjectPooler();
    ATDEnemy* actualEnemy = objectRef->TDGetEnemyFromPool();

    if (!actualEnemy)
    {
        return nullptr;
    }

    UTDWeightManager* weightManager = UTDGameData::TDGetWeightManager();

    if (!weightManager)
    {
        return nullptr;
    }

    FTDEnemiesDataTable Row;
    weightManager->TDGetRowFromDataTable(enemyName, Row);
    weightManager->TDSetEnemyValues(actualEnemy, Row);
    EnemiesToKill += 1;

    ATDEnemy* enemyInstigator = Cast<ATDEnemy>(_instigator);
    ATDEnemyController* enemyController = actualEnemy->GetController<ATDEnemyController>();
    UBlackboardComponent* blackboard = enemyController->GetBlackboardComponent();

    ATDPathPoint* firstWaypoint = enemyInstigator->PathPointsArray[0];

    blackboard->SetValueAsObject(FName(TEXT("WaypointActor")), firstWaypoint);
    blackboard->SetValueAsVector(FName(TEXT("WaypointPosition")), firstWaypoint->GetActorLocation());


    actualEnemy->TDSetPath(firstWaypoint);
    actualEnemy->TDSetActive();

    return actualEnemy;
}

GamePhase ATDRoundManager::TDGetActualPhase()
{
    return actualPhase;
}
