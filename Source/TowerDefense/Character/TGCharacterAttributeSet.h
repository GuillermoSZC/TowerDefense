// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "GameLogic/TGAttributeSet.h"
#include "TGCharacterAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UTGCharacterAttributeSet : public UTGAttributeSet
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


protected:


private:




};
