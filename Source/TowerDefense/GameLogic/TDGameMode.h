// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TDObjectPooler.h"
#include "TDGameMode.generated.h"

class ATDEnemy;

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
        TSubclassOf<ATDEnemy> EnemyClass;




protected:
	

private:


public:


protected:

    void StartPlay() override;


    void StartToLeaveMap() override;


    void Reset() override;


private:


};
