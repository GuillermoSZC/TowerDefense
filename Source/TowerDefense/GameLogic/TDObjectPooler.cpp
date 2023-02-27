// Fill out your copyright notice in the Description page of Project Settings.


#include "GameLogic/TDObjectPooler.h"
#include "TDGameData.h"
#include "Character/TDEnemy.h"

ATDObjectPooler* ATDObjectPooler::OwnerPooler = nullptr;

ATDObjectPooler* ATDObjectPooler::TDGetObjectPooler(TSubclassOf<ATDObjectPooler> _classRef)
{

	if (OwnerPooler == nullptr)
	{
		UWorld* actualWorld = UTDGameData::TDGetWorld();
		FActorSpawnParameters paramet;
		//OwnerPooler = Cast<ATDObjectPooler>(actualWorld->SpawnActor(ATDObjectPooler::StaticClass()));
		OwnerPooler = actualWorld->SpawnActor<ATDObjectPooler>(_classRef);
	}

	return OwnerPooler;
}





// Sets default values
ATDObjectPooler::ATDObjectPooler()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATDObjectPooler::BeginPlay()
{
	Super::BeginPlay();
	
}



// Called every frame
void ATDObjectPooler::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

