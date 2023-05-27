// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameplayEffectTypes.h"
#include "AttributeSet.h"

#include "TDGameData.generated.h"

class UWorld;
class ATDEnemy;
class UTDGameplayEventData;
class UTDWeightManager;
class UAbilitySystemComponent;



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
	static UPROPERTY(Transient) TArray<ATDSpawner*> spawnerArray;
	static UPROPERTY(Transient) UTDGameplayEventData* abilityData;
	static UPROPERTY(Transient) ATDBase* baseRef;
	static UPROPERTY(Transient) UTDWeightManager* weightManagerRef;
	static UPROPERTY(Transient) ATDGameMode* GameModeRef;
	static UPROPERTY(Transient) ATDRoundManager* RoundManagerRef;

	static UPROPERTY(Transient) ATDObjectPooler* ObjectPoolerRef;
	static UPROPERTY(Transient) UTDGameInstance* GameInstanceRef;

	static UPROPERTY(Transient) ATDPlayerCharacter* playerRef;

	static UPROPERTY(Transient) ATDCostManager* CostManagerRef;






	UFUNCTION(BlueprintPure)
	static UWorld* TDGetWorld();

	UFUNCTION(BlueprintCallable)
	static void TDSetWorld(UWorld* _ActualMap);

	UFUNCTION(BlueprintPure)
    static TArray<ATDEnemy*> TDGetEnemiesArray();

	UFUNCTION(BlueprintCallable)
    static void TDAddEnmemyToArray(ATDEnemy* _ActualEnemy);

    UFUNCTION(BlueprintCallable)
    static void TDRemoveEnmemyToArray(ATDEnemy* _ActualEnemy);

	UFUNCTION(BlueprintCallable)
	static void TDDisableAllEnemies();

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
	
	UFUNCTION(BlueprintPure)
	static ATDBase* TDGetBaseActor();

    UFUNCTION()
        static void TDSetBaseActor(ATDBase* _baseRef);


    UFUNCTION(BlueprintPure)
        static UTDWeightManager* TDGetWeightManager();

    UFUNCTION()
        static void TDSetWeightManager(UTDWeightManager* _weightManagerRef);



	UFUNCTION()
	static void TDaddSpawnerActor(ATDSpawner* _spawnerRef);

	UFUNCTION()
	static ATDSpawner* TDGetSpanwerActor();

	UFUNCTION(BlueprintPure)
	static ATDGameMode* TDGetGameMode();

	UFUNCTION()
	static void TDSetGameInstance(UTDGameInstance* _gameinmstanceRef);


	static UTDGameInstance* TDGetGameInstance();


    UFUNCTION()
        static void TDSetGameMode(ATDGameMode* _gameModeRef);



	UFUNCTION(BlueprintCallable)
	static void TDSetRoundManager(ATDRoundManager* _RoundManagerRef);


    UFUNCTION(BlueprintPure)
        static ATDRoundManager* TDGetRoundManager();


    UFUNCTION(BlueprintCallable)
        static void TDSetObjectPooler(ATDObjectPooler* _ObjectPooler);


    UFUNCTION(BlueprintCallable)
        static ATDObjectPooler* TDGetObjectPooler();



	UFUNCTION(BlueprintPure)
	static ATDPlayerCharacter* TDGetPlayerRef();

	UFUNCTION()
	static void TDSetPlayerRef(ATDPlayerCharacter* _ref);


	UFUNCTION(BlueprintPure)
	static ATDCostManager* TDGetCostManager();


	UFUNCTION()
	static void TDSetCostManager(ATDCostManager* _ref);


	UFUNCTION(BlueprintPure)
	static FText TDConvertIntToFText(int32 _num);


	//Debug
	UFUNCTION(BlueprintCallable)
	static void TDSpawnEnemyDebug();

	static void TDCreateAndApplyGE(UAbilitySystemComponent* _ASC, FGameplayAttribute _attribute, EGameplayModOp::Type _modType, float _value);

};
