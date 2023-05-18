// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TDTowerEnum.h"
#include "TDCostManager.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class TOWERDEFENSE_API UTDCostManager : public UObject
{
	GENERATED_BODY()
	


public:

	UTDCostManager();

public:
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TMap<ETowers, int32> TowerBuyCost;
	
protected:

private:

public:
	UFUNCTION(BlueprintNativeEvent,BlueprintPure)
	int32 TDCalculateTowerBuyCost(ETowers _tower);


protected:

private:

};
