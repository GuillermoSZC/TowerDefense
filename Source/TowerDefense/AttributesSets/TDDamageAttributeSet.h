// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameLogic/TDAttributeSet.h"
#include "TDDamageAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UTDDamageAttributeSet : public UTDAttributeSet
{
	GENERATED_BODY()
	

		public:


public:


    UPROPERTY(Category = "Ability System | Attributes", VisibleAnywhere, BlueprintReadOnly)
        FGameplayAttributeData attackDamage;

    UPROPERTY(Category = "Ability System | Attributes", VisibleAnywhere, BlueprintReadOnly)
        FGameplayAttributeData attackSpeed;

    UPROPERTY(Category = "Ability System | Attributes", VisibleAnywhere, BlueprintReadOnly)
        FGameplayAttributeData attackRange;

protected:


private:


public:

        ATTRIBUTE_ACCESSORS(UTDDamageAttributeSet, attackDamage)
        ATTRIBUTE_ACCESSORS(UTDDamageAttributeSet, attackSpeed)
        ATTRIBUTE_ACCESSORS(UTDDamageAttributeSet, attackRange)


protected:


private:


};
