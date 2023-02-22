// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "../GameLogic/TDAttributeSet.h"
#include "TDBaseAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UTDBaseAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:

    UTDBaseAttributeSet();

public:

    UPROPERTY(Category = "Ability System | Attributes", VisibleAnywhere, BlueprintReadOnly)
        FGameplayAttributeData health;

protected:


private:


public:

    ATTRIBUTE_ACCESSORS(UTDBaseAttributeSet, health)

protected:


private:
};
