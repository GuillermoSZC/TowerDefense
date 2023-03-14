// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TDObjectPooler.h"
#include "ElementsEnum.h"
#include "TDRoundManager.h"
#include "TDGameMode.generated.h"

class ATDEnemy;
class UDataTable;

/**
 *
 */
UCLASS()
class TOWERDEFENSE_API ATDGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:

    ATDGameMode();



public:

    UPROPERTY(EditDefaultsOnly)
        TSubclassOf<ATDObjectPooler> objectPoolerClass;

    UPROPERTY(EditDefaultsOnly)
        TSubclassOf<ATDRoundManager> RoundManagerClass;

    UPROPERTY(EditDefaultsOnly)
        TSubclassOf<ATDEnemy> EnemyClass;


    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
        UDataTable* statsDatatable;

    UPROPERTY(EditDefaultsOnly)
        TMap<EElements, UTDElement*> elementsDataAssets;


protected:


private:


public:

    UTDElement* TDGetDataAssetFromElement(EElements _keyElement);

protected:
    void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

    void StartPlay() override;

    void StartToLeaveMap() override;


    void Reset() override;


private:


};
