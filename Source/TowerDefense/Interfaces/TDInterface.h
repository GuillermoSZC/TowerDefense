// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TDInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UTDInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TOWERDEFENSE_API ITDInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:


	//Este se puede implementar en BP y en C++
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
         int TGGApplyEffect();

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	void TDResetAttackTimer();

	//Este solo se puede implementar en BP
//     UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
//         const bool TGGApplyEffect2() const;






};
