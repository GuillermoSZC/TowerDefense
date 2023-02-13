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
        FGameplayAttributeData damage;

    UPROPERTY(Category = "Ability System | Attributes", VisibleAnywhere, BlueprintReadOnly)
        FGameplayAttributeData speed;

    UPROPERTY(Category = "Ability System | Attributes", VisibleAnywhere, BlueprintReadOnly)
        FGameplayAttributeData attackSpeed;

protected:


private:


public:

    ATTRIBUTE_ACCESSORS(UTDCharacterAttributeSet, maxHealth)
        ATTRIBUTE_ACCESSORS(UTDCharacterAttributeSet, health)
        ATTRIBUTE_ACCESSORS(UTDCharacterAttributeSet, damage)
        ATTRIBUTE_ACCESSORS(UTDCharacterAttributeSet, speed)
        ATTRIBUTE_ACCESSORS(UTDCharacterAttributeSet, attackSpeed)


protected:


private:




};
