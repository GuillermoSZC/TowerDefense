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
	TArray<EElements> actualRoundElements;

	UPROPERTY(Transient)
	TArray<ATDEnemy*> preparedEnemies;


public:

	/// <summary>
	/// Take an enemy from the prepared enemies to spawn it on the map
	/// </summary>
	UFUNCTION()
	void TDSpawnEnemy();

	UFUNCTION()
	void TDSetDataTable(UDataTable* _ref);

	/// <summary>
	/// Prepare the round. It select the enemies with the DataTable Values and prepare it for the start of the combat Round.
	/// Also clean the previous values for this new round.
	/// </summary>
	/// <param name="_atualRound"></param>
	/// <param name="_roundElement">Set randomly an element fot every enemy</param>
	/// <returns>It returns the amount of enemies the player will face to</returns>
	UFUNCTION()
	int32 TDSetActualRound(int32& _atualRound, TArray<EElements> _roundElement);

	//Get a Row from the DataTable with the name of the Row.
	UFUNCTION()
	void TDGetRowFromDataTable(FName _RowName, FTDEnemiesDataTable& _Row);

	//Set the values from the DataTable to the enemy passed
	void TDSetEnemyValues(ATDEnemy* _enemyRef, FTDEnemiesDataTable& Row);

protected:

private:

	//Get a randomly a Row from the DataTable
	FTDEnemiesDataTable* TDSelectRandomRowFromDataTable();

	
};
