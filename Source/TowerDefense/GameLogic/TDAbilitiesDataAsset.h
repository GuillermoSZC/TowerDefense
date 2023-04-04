// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

#include "TDAbilitiesDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UTDAbilitiesDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:

public:

	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<class UGameplayAbility>> abiliyList;


protected:

private:

public:

protected:

private:


	
};
