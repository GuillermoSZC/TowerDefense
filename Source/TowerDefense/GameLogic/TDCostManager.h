// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TDTowerEnum.h"
#include "TDBuyStruct.h"
#include "TDCostManager.generated.h"

/**
 *
 */
UCLASS(BlueprintType, Blueprintable)
class TOWERDEFENSE_API ATDCostManager : public AActor
{
    GENERATED_BODY()



public:

    ATDCostManager();

public:
    UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
        TMap<ETowers, FBuyCost> TowerBuyCost;

protected:

private:

public:

    UFUNCTION(BlueprintNativeEvent)
        FBuyCost TDCalculateTowerBuyCost(ELootItems _Item);

    UFUNCTION()
        bool TDCanAffordBuy(ELootItems _Item);




protected:

private:

};
