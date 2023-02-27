// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TDWeightManager.generated.h"

class ATDEnemy;

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UTDWeightManager : public UObject
{
	GENERATED_BODY()

private:

	UTDWeightManager();

public:

	UPROPERTY(EditAnywhere)
	int WeightPerRound = 1;

protected:

private:

	static UPROPERTY(Transient) UTDWeightManager* weightManager;

public:

	UFUNCTION()
	UTDWeightManager* TDGetWeightManager();


	UFUNCTION()
	void StartSpawn(TSubclassOf<ATDEnemy> _enemyClass);


protected:

private:



	
};
