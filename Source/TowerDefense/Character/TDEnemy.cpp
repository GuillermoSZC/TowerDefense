#include "Character/TDEnemy.h"

ATDEnemy::ATDEnemy()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ATDEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATDEnemy::BeginPlay()
{
	Super::BeginPlay();
}
