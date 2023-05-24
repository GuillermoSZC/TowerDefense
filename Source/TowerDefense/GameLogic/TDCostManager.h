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
        TMap<ELootItems, FBuyCost> TowerBuyCost;

protected:

private:

public:

    UFUNCTION(BlueprintNativeEvent)
        void TDCalculateTowerBuyCost(FBuyCost& _cost, ELootItems _Item);

    UFUNCTION()
        bool TDCanAffordBuy(ELootItems _Item);


    UFUNCTION(BlueprintNativeEvent)
    void TDCalculateTowerUpgradeCost(FBuyCost& _cost, ELootItems _Item, int32 _actualLevel);

       UFUNCTION(BlueprintNativeEvent)
    void TDCalculateElementChange(FBuyCost& _cost, EElements _Element, EElements _actualElement);


protected:

private:

};
