// Fill out your copyright notice in the Description page of Project Settings.


#include "Map/TDSpawner.h"
#include "GameLogic/TDGameData.h"
#include "GameLogic/TDPathPoint.h"
#include "Character/TDEnemy.h"
#include "Character/TDEnemyController.h"
#include "AIModule/Classes/BehaviorTree/BlackboardComponent.h"
#include "Components/CapsuleComponent.h"



// Sets default values
ATDSpawner::ATDSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATDSpawner::BeginPlay()
{
	Super::BeginPlay();

	UTDGameData::TDaddSpawnerActor(this);
	
}

// Called every frame
void ATDSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATDSpawner::TDSpawnEnemy(ATDEnemy* _enemyRef)
{


	ATDEnemyController* enemyController =_enemyRef->GetController<ATDEnemyController>();
    UBlackboardComponent* blackboard = enemyController->GetBlackboardComponent();


	if (firstWaypoint)
	{
        blackboard->SetValueAsObject(FName(TEXT("WaypointActor")), firstWaypoint);
        blackboard->SetValueAsVector(FName(TEXT("WaypointPosition")), firstWaypoint->GetActorLocation());
        _enemyRef->TDSetPath(firstWaypoint);
	}


	FVector spawnerPos = GetActorLocation();
	spawnerPos.Z += _enemyRef->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
	_enemyRef->SetActorLocation(spawnerPos);
	

   

}

