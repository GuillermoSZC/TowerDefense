// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TDEnemiesDataTable.h"
#include "TDWeightManager.generated.h"

class ATDEnemy;


/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UTDWeightManager : public UObject
{
	GENERATED_BODY()

public:
	UTDWeightManager();

public:

	UPROPERTY(EditAnywhere)
	int32 WeightPerRound;


    UPROPERTY(EditAnywhere)
        int32 ActualRound;

	TMap<int8, int32> enemiesPerClass;


protected:

private:



    UPROPERTY(Transient)
        UDataTable* enemiesDatatable;

	UPROPERTY()
	int32 actualWegith = 0;

	UPROPERTY()
	int8 licheCounter;

	UPROPERTY()
	TArray<EElements> actualRoundElements;

	UPROPERTY(Transient)
	TArray<ATDEnemy*> preparedEnemies;


public:


	UFUNCTION()
	void TDStartSpawn();

	UFUNCTION()
	void TDSetDataTable(UDataTable* _ref);


	UFUNCTION()
	int32 TDSetActualRound(int32& _atualRound, TArray<EElements> _roundElement);


	UFUNCTION()
	void TDGetRowFromDataTable(FName _RowName, FTDEnemiesDataTable& _Row);

	void TDSetEnemyValues(ATDEnemy* _enemyRef, FTDEnemiesDataTable& Row);

protected:

private:


	FTDEnemiesDataTable* TDSelectRandomRowFromDataTable();

	
};
