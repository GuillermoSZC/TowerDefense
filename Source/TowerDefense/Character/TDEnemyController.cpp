// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TDEnemyController.h"

void ATDEnemyController::BeginPlay()
{
    Super::BeginPlay();
    

    int32 x = 1;
    int32 y = 3;


    RandomSpawnNumber = FMath::RandRange(x, y);

    

    GEngine->AddOnScreenDebugMessage(0, 10, FColor::Orange, FString::SanitizeFloat((float)RandomSpawnNumber));

}

int32 ATDEnemyController::TDGetRandomSpawnNunber()
{
    return RandomSpawnNumber;
}
