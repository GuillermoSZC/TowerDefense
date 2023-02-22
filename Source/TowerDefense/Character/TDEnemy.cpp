#include "Character/TDEnemy.h"
#include "GameLogic/TDGameData.h"

ATDEnemy::ATDEnemy()
{
    PrimaryActorTick.bCanEverTick = true;

	refreshPathTime = 0.2f;
	tickCounterTime = 0.f;

}

void ATDEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (tickCounterTime >= refreshPathTime)
	{
		pathDsitance = TDGetPathDistance();

		tickCounterTime -= refreshPathTime;

	}

	tickCounterTime += DeltaTime;

}

float ATDEnemy::TDGetPathDistance()
{
	return  pathDsitance;
}

void ATDEnemy::BeginPlay()
{
	Super::BeginPlay();


	UTDGameData::TDAddEnmemyToArray(this);
}


