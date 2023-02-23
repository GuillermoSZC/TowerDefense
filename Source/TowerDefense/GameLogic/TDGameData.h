// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TDGameData.generated.h"

class UWorld;
class ATDEnemy;
class UTDGameplayEventData;



/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UTDGameData : public UBlueprintFunctionLibrary
{
    GENERATED_UCLASS_BODY()

public:



	UFUNCTION()
	static void TDResetGameData();





	static UPROPERTY(Transient) UWorld* gameWorld;
	static UPROPERTY(Transient) TArray<ATDEnemy*> enemiesArray;
	static UPROPERTY(Transient) UTDGameplayEventData* abilityData;







	UFUNCTION(BlueprintCallable)
	static UWorld* TDGetWorld();

	UFUNCTION(BlueprintCallable)
	static void TDSetWorld(UWorld* _ActualMap);

	UFUNCTION(BlueprintCallable)
    static TArray<ATDEnemy*> TDGetEnemiesArray();

	UFUNCTION(BlueprintCallable)
    static void TDAddEnmemyToArray(ATDEnemy* _ActualEnemy);

	UFUNCTION(BlueprintPure)
    static UTDGameplayEventData* TDGetAbilityStrcut();

	UFUNCTION(BlueprintCallable)
    static void TDSetAbilityStruct(UTDGameplayEventData* _NewAbilityData);

    UFUNCTION(BlueprintPure)
        static UTDGameplayEventData* TDGetAbilityStruct();

    UFUNCTION(BlueprintPure)
    static ATDEnemy* TDGetNearEnemyToBase();

    UFUNCTION(BlueprintPure)
	static ATDEnemy* TDGetNearEnemyFromArrayToBase(TArray<AActor*> _enemies);
	
};
