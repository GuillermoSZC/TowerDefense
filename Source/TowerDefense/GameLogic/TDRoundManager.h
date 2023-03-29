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



/**
 *
 */
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

    bool isSawning = false;

    TArray<EElements> actualRoundElements;


    GamePhase actualPhase = GamePhase::BuyPhase;

    


public:
    UFUNCTION(BlueprintCallable)
        void TDStartRound();


        UFUNCTION(BlueprintCallable)
        void TDPrepareCombatRound();


    UFUNCTION(BlueprintCallable)
        void TDStopRound();



    

	UFUNCTION()
	void TDPostBeginPlay();



    virtual void Tick(float DeltaSeconds) override;


    void TDEnemyKillCounter(int32& _weight);

    UFUNCTION(BlueprintCallable)
        float TDGetTimeRound();

    UFUNCTION(BlueprintPure)
        int32 TDGetActualRound();
protected:

    virtual void BeginPlay() override;

private:


    void TDStartBuyPhase();

    void TDStartCombatPhase();
};
