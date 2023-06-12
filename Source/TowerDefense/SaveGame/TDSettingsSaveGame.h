// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "TDSettingsSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UTDSettingsSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:

	UTDSettingsSaveGame();

public:
	UPROPERTY()
	float sfxVolumen;
	UPROPERTY()
	float musicVolumen;
		UPROPERTY()
	float masterVolumen;


protected:

private:

public:

protected:

private:


};
