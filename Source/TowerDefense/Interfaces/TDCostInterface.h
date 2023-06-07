// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameLogic/TDBuyStruct.h"
#include "TDCostInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UTDCostInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 *
 */
class TOWERDEFENSE_API ITDCostInterface
{
    GENERATED_BODY()

        // Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
    //TowerCost, TowerUpgrade and Player Upgrades
    UFUNCTION(BlueprintNativeEvent)
        void TDCalcultateCostWithLoot(FBuyCost& _cost, ELootItems _item = ELootItems::None);

    //GemCost 
    UFUNCTION(BlueprintNativeEvent)
        void TDCalculateElementChangeCost(FBuyCost& _cost, ELootItems _itemElement);

    //TowerCost, TowerUpgrade and Player Upgrades
    UFUNCTION(BlueprintNativeEvent)
        bool TDCanAffordCostWithLoot(FBuyCost& _cost);


    UFUNCTION(BlueprintNativeEvent)
        bool TDCommitBuyUpgrade(ELootItems _item = ELootItems::None);


    UFUNCTION()
    virtual void TDTriggerOpenUI();


    //Este solo se puede implementar en BP
//     UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
//         const bool TGGApplyEffect2() const;






};
