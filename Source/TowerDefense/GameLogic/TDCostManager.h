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

//     UFUNCTION(BlueprintNativeEvent)
//         void TDCalculateTowerBuyCost(FBuyCost& _cost);
 

    UFUNCTION(BlueprintNativeEvent)
    void TDCalculateUpgradeCost(FBuyCost& _cost, int32 _actualLevel);

    


       UFUNCTION(BlueprintNativeEvent)
    void TDCalculateElementChange(FBuyCost& _cost, EElements _Element, EElements _actualElement);

       
    //Only use for tower buy and Upgrades
    UFUNCTION()
        bool TDCanAffordBuy(FBuyCost& _cost);


    void TDCommitResources(FBuyCost& _cost);

      // bool TDCanAffordElementChange(FBuyCost& _cost, ELootItems _Item);

protected:

private:

};
