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

    UFUNCTION(BlueprintNativeEvent)
    void TDCalcultateCostWithLoot(FBuyCost& _cost, ELootItems _item);

     UFUNCTION(BlueprintNativeEvent)
    void TDCalcultateCost(FBuyCost& _cost);


        UFUNCTION(BlueprintNativeEvent)
    void TDCalculateElementChangeCost(FBuyCost& _cost, EElements _element);



    //Este solo se puede implementar en BP
//     UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
//         const bool TGGApplyEffect2() const;






};
