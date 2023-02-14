// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TDGameData.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UTDGameData : public UObject
{
	GENERATED_BODY()

private:


	static UPROPERTY(Transient) UWorld* gameWorld;



public:

	static UFUNCTION(BlueprintCallable) UWorld* TDGetWorld();
	static UFUNCTION(BlueprintCallable) void TDSetWorld(UWorld* _ActualMap);
	
};
