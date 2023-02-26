// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TDEnemyController.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API ATDEnemyController : public AAIController
{
	GENERATED_BODY()

public:


public:


protected:



	void BeginPlay() override;

private:
	

public:

	int32 TDGetRandomSpawnNunber();

protected:


private:


};
