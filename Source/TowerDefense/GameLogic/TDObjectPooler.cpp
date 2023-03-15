// Fill out your copyright notice in the Description page of Project Settings.


#include "GameLogic/TDObjectPooler.h"
#include "TDGameData.h"
#include "Character/TDEnemy.h"


ATDEnemy* ATDObjectPooler::TDGetEnemyFromPool()
{
    if (!disabledEnemies.IsEmpty())
    {
        ATDEnemy* enemyRef = disabledEnemies[0];
        disabledEnemies.RemoveAt(0);
        activeEnemies.Add(enemyRef);
        return enemyRef;
    }
    return nullptr;
}

void ATDObjectPooler::TDAddEnemyToPool(ATDEnemy* _enemyRef)
{
    _enemyRef->TDSetDisable();
    activeEnemies.Remove(_enemyRef);
    disabledEnemies.Add(_enemyRef);

}

// Sets default values
ATDObjectPooler::ATDObjectPooler()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

}

ATDObjectPooler::~ATDObjectPooler()
{
   
}

// Called when the game starts or when spawned
void ATDObjectPooler::BeginPlay()
{
    Super::BeginPlay();

    UWorld* actualWorld = UTDGameData::TDGetWorld();

    for (int i = 0; i < InitialSpawn; ++i)
    {
        ATDEnemy* enemyRef = actualWorld->SpawnActor<ATDEnemy>(enemiesClasses[0]);

        enemyRef->TDSetDisable();
        disabledEnemies.Add(enemyRef);
    }



}



// Called every frame
void ATDObjectPooler::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

