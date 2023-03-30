// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameLogic/TDAttributeSet.h"
#include "TDHealthAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UTDHealthAttributeSet : public UTDAttributeSet
{
	GENERATED_BODY()
	

		public:


public:


    UPROPERTY(Category = "Ability System | Attributes", VisibleAnywhere, BlueprintReadOnly)
        FGameplayAttributeData maxHealth;

    UPROPERTY(Category = "Ability System | Attributes", VisibleAnywhere, BlueprintReadOnly)
        FGameplayAttributeData health;

protected:


private:


public:

    ATTRIBUTE_ACCESSORS(UTDHealthAttributeSet, maxHealth)
        ATTRIBUTE_ACCESSORS(UTDHealthAttributeSet, health)



protected:


private:


};
