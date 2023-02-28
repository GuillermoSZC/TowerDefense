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
	int32 WeightPerRound = 1;


    UPROPERTY(EditAnywhere)
        int32 ActualRound = 9;


protected:

private:

	static UPROPERTY(Transient) UTDWeightManager* weightManager;


    UPROPERTY(Transient)
        UDataTable* enemiesDatatable;

	UPROPERTY()
	int32 actualWegith = 0;
public:

	UFUNCTION()
	UTDWeightManager* TDGetWeightManager();


	UFUNCTION()
	void TDStartSpawn();

	UFUNCTION()
	void TDSetDataTable(UDataTable* _ref);


protected:

private:


	void TDSetEnemyValues(ATDEnemy* _enemyRef);
	
};
