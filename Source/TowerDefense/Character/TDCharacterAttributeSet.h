// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "GameLogic/TDAttributeSet.h"
#include "TDCharacterAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UTDCharacterAttributeSet : public UTDAttributeSet
{
	GENERATED_BODY()
	
public:


public:


    UPROPERTY(Category = "Ability System | Attributes", VisibleAnywhere, BlueprintReadOnly)
        FGameplayAttributeData maxHealth;

    UPROPERTY(Category = "Ability System | Attributes", VisibleAnywhere, BlueprintReadOnly)
        FGameplayAttributeData health;

    UPROPERTY(Category = "Ability System | Attributes", VisibleAnywhere, BlueprintReadOnly)
        FGameplayAttributeData attackDamage;

    UPROPERTY(Category = "Ability System | Attributes", VisibleAnywhere, BlueprintReadOnly)
        FGameplayAttributeData movementSpeed;

    UPROPERTY(Category = "Ability System | Attributes", VisibleAnywhere, BlueprintReadOnly)
        FGameplayAttributeData attackSpeed;

    UPROPERTY(Category = "Ability System | Attributes", VisibleAnywhere, BlueprintReadOnly)
        FGameplayAttributeData attackRange;

protected:


private:


public:

    ATTRIBUTE_ACCESSORS(UTDCharacterAttributeSet, maxHealth)
        ATTRIBUTE_ACCESSORS(UTDCharacterAttributeSet, health)
        ATTRIBUTE_ACCESSORS(UTDCharacterAttributeSet, attackDamage)
        ATTRIBUTE_ACCESSORS(UTDCharacterAttributeSet, movementSpeed)
        ATTRIBUTE_ACCESSORS(UTDCharacterAttributeSet, attackSpeed)
        ATTRIBUTE_ACCESSORS(UTDCharacterAttributeSet, attackRange)


protected:


private:




};
