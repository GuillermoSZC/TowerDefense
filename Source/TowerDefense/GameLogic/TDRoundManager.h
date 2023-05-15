// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TDRoundManager.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBuyPhaseStartSignature, int32, round);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCombatPhaseStartSignature, int32, round);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnemyKillSignature, int32, _value);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnElementSelectionSignature, TArray<EElements>&, _elements);


class UTDRoundElementsType;


UENUM(BlueprintType)
enum class GamePhase : uint8
{
    BuyPhase = 0,
    CombatPhase = 1
};

UCLASS(BlueprintType, Blueprintable)
class TOWERDEFENSE_API ATDRoundManager : public AActor
{
    GENERATED_BODY()


public:

    ATDRoundManager();

    ~ATDRoundManager();

public:

    UPROPERTY(EditAnywhere, Instanced)
        TArray<UTDRoundElementsType*> RoundElements;

    UPROPERTY(EditDefaultsOnly)
        int32 timeBuyPhase = 20.f;



    //Delegates
    FOnBuyPhaseStartSignature FOnBuyPhaseStartDelegate;
    FOnCombatPhaseStartSignature FOnCombatPhaseStartDelegate;
    FOnElementSelectionSignature FOnElementSelectionDelegate;
    FOnEnemyKillSignature FOnEnemyKillDelegate;

protected:
private:

    int32 killedWegith = 0;

    int32 EnemiesToKill = 0;

    int32 actualRound = 0;

    float timeRound = 0;

    float timeperSpawn = 0.7f;


    TArray<EElements> actualRoundElements;


    GamePhase actualPhase = GamePhase::BuyPhase;




public:

    //Prepare the elements for the actual round and prepare all the enemies for the actual round selected with the weightManager
    UFUNCTION(BlueprintCallable)
        void TDPrepareCombatRound();

    UFUNCTION()
        void TDPostBeginPlay();

    virtual void Tick(float DeltaSeconds) override;

    //Reduce the amount of the actuals enemies of this round by one. If the amount is <= 0 end combatPhase and start buyPhase
    void TDMinusEnemyKillCounter();

    //Increase the amount of the actuals enemies of this round by one
    UFUNCTION(BlueprintCallable)
        void TDAddEnemyKilCounter();


    UFUNCTION(BlueprintCallable)
        float TDGetTimeRound();

    UFUNCTION(BlueprintPure)
        int32 TDGetActualRound();

    /// <summary>
    /// Get an enemy from the pool, prepare with the values from the DataTable with the enemyName and the actor that make this and spawn with the new enemy
    /// </summary>
    /// <param name="enemyName">Row Name of the EnemyDataTable</param>
    /// <param name="_instigator">Enemy who activated this from an ability</param>
    /// <returns>Returns the new enemy created</returns>
    UFUNCTION(BlueprintCallable)
        ATDEnemy* TDCreateEnemy(FName enemyName, AActor* _instigator);

    UFUNCTION(BlueprintPure)
        GamePhase TDGetActualPhase();

protected:

    virtual void BeginPlay() override;

private:

    //Change to BuyPhase and activate the delegate for all the objects listening
    void TDStartBuyPhase();

    //Change to CombatPhase and activate the delegate for all the objects listening
    void TDStartCombatPhase();
};
