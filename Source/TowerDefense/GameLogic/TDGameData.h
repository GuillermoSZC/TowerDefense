// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Character/TDEnemy.h"
#include "Gas/TDGameplayEventData.h"
#include "TDGameData.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class TOWERDEFENSE_API UTDGameData : public UObject
{
	GENERATED_BODY()

private:


	static UPROPERTY(Transient) UWorld* gameWorld;
	static UPROPERTY(Transient) TArray<ATDEnemy*> enemiesArray;
	static UPROPERTY(Transient) UTDGameplayEventData* abilityData;


public:


	static UFUNCTION() void TDResetGameData();


	static UFUNCTION(BlueprintCallable) UWorld* TDGetWorld();
	static UFUNCTION(BlueprintCallable) void TDSetWorld(UWorld* _ActualMap);


    static UFUNCTION(BlueprintCallable)  TArray<ATDEnemy*> TDGetEnemiesArray();
    static UFUNCTION(BlueprintCallable) void TDAddEnmemyToArray(ATDEnemy* _ActualEnemy);


    static UFUNCTION(BlueprintCallable) UTDGameplayEventData* TDGetAbilityStrcut();
    static UFUNCTION(BlueprintCallable) void TDSetAbilityStruct(UTDGameplayEventData* _NewAbilityData);

	
};
