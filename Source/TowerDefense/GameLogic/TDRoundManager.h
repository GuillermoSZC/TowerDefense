// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TDRoundManager.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBuyPhaseStartSignature, int32, round);


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


private:

    ATDRoundManager();

    ~ATDRoundManager();

public:

    UPROPERTY(EditAnywhere, Instanced)
        TArray<UTDRoundElementsType*> RoundElements;


    UPROPERTY(EditDefaultsOnly)
        int32 timeBuyPhase = 20.f;


    FOnBuyPhaseStartSignature FOnBuyPhaseStartDelegate;

protected:





private:

    int32 killedWegith = 0;

    int32 RoundWeight = 0;

    int32 actualRound = 0;

    float timeRound = 0;

    float timeperSpawn = 0.7f;

    static ATDRoundManager* managerRef;

    bool isSawning = false;

    TArray<EElements> actualRoundElements;


    GamePhase actualPhase = GamePhase::BuyPhase;

    


public:
    UFUNCTION(BlueprintCallable)
        void TDStartRound();

    UFUNCTION(BlueprintCallable)
        void TDStopRound();




     UFUNCTION(BlueprintPure)
    static ATDRoundManager* TDGetRoundManager();

    static ATDRoundManager* TDGetRoundManager(TSubclassOf<ATDRoundManager> _classRef);

    virtual void Tick(float DeltaSeconds) override;


    void TDEnemyKillWeight(int32& _weight);

    UFUNCTION(BlueprintCallable)
        float TDGetTimeRound();


protected:

    virtual void BeginPlay() override;

private:


    void TDStartBuyPhase();

    void TDStartCombatPhase();
};
