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
#include "Map/TDSpawner.h"





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

void ATDRoundManager::TDStartBuyPhase_Implementation()
{
    timeRound = timeBuyPhase;
    actualPhase = GamePhase::BuyPhase;
    TDPrepareCombatRound();

    FOnBuyPhaseStartDelegate.Broadcast(actualRound);
}

void ATDRoundManager::TDStartCombatPhase_Implementation()
{
    actualPhase = GamePhase::CombatPhase;
    timeRound = timeperSpawn;

    FOnCombatPhaseStartDelegate.Broadcast(actualRound);
}


void ATDRoundManager::TDSpawnEnemy()
{
    ATDEnemy* actualEnemy = nullptr;
    if (!heapEnemies.IsEmpty())
    {
        actualEnemy = heapEnemies[0];
        heapEnemies.Remove(actualEnemy);
    }

    if (actualEnemy)
    {
        ATDSpawner* spawnerRef = UTDGameData::TDGetSpanwerActor();
        spawnerRef->TDPlaceEnemy(actualEnemy);
        actualEnemy->TDSetActive();
    }

}

void ATDRoundManager::TDPrepareCombatRound()
{
    ++actualRound;

    

    if (!isInfinite && actualRound > MaxGameRound)
    {
        TDEndGameAction();
        return;
    }

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

    heapEnemies = UTDGameData::TDGetWeightManager()->TDSetActualRound(actualRound, actualRoundElements);
    enemiesAlive = heapEnemies;
    FOnEnemyKillDelegate.Broadcast(heapEnemies.Num());
}



void ATDRoundManager::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    if (actualPhase == GamePhase::CombatPhase)
    {
        if (timeRound >= timeperSpawn)
        {

            TDSpawnEnemy();
            timeRound -= timeperSpawn;
        }
        timeRound += DeltaSeconds;
    }

    if (actualPhase == GamePhase::BuyPhase)
    {
        if (!timePaused)
        {
            if (timeRound <= 0.f)
            {
                TDStartCombatPhase();
            }
            timeRound -= DeltaSeconds;
        }

    }
}

void ATDRoundManager::TDMinusEnemyKillCounter(ATDEnemy* _enemyDeath)
{
    enemiesAlive.Remove(_enemyDeath);

    FOnEnemyKillDelegate.Broadcast(enemiesAlive.Num());

    if (enemiesAlive.IsEmpty())
    {
        TDStartBuyPhase();
    }
}



void ATDRoundManager::TDAddEnemyKilCounter(ATDEnemy* _newEnemy)
{
    if (!enemiesAlive.Contains(_newEnemy))
    {
        enemiesAlive.Add(_newEnemy);
    }
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

    if (!enemyInstigator->PathPointsArray.IsEmpty())
    {
        ATDPathPoint* firstWaypoint = enemyInstigator->PathPointsArray[0];

        blackboard->SetValueAsObject(FName(TEXT("WaypointActor")), firstWaypoint);
        blackboard->SetValueAsVector(FName(TEXT("WaypointPosition")), firstWaypoint->GetActorLocation());
        actualEnemy->TDSetPath(firstWaypoint);


    }
    else
    {
        blackboard->SetValueAsObject(FName(TEXT("BaseBuild")), UTDGameData::TDGetBaseActor());
    }

    actualEnemy->TDSetActive();

    return actualEnemy;
}

GamePhase ATDRoundManager::TDGetActualPhase()
{
    return actualPhase;
}

void ATDRoundManager::TDSetTimePaused(bool _newState)
{
    timePaused = _newState;
}

void ATDRoundManager::TDModifyBuyPhaseTime(float _time)
{
    timeRound += _time;
}

bool ATDRoundManager::TDGetIsInfinite() const
{
    return isInfinite;
}

void ATDRoundManager::TDSetIsInfinite(bool _value)
{
    isInfinite = _value;
}
