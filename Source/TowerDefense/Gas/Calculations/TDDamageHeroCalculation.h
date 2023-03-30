// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "TDMacros.h"
#include "AttributesSets/TDHealthAttributeSet.h"
#include "AttributesSets/TDDamageAttributeSet.h"
#include "TDDamageHeroCalculation.generated.h"

/**
 *
 */

struct TDAttributeCaptureDamageHero
{
    TDDECLARE_ATTRIBUTE_CAPTUREDEF(health, Target);
    TDDECLARE_ATTRIBUTE_CAPTUREDEF(attackDamage, Source);

    TDAttributeCaptureDamageHero()
    {
        TDDEFINE_ATTRIBUTE_CAPTUREDEF(UTDHealthAttributeSet, health, Target, false);
        TDDEFINE_ATTRIBUTE_CAPTUREDEF(UTDDamageAttributeSet, attackDamage, Source, false);
    }
};



UCLASS()
class TOWERDEFENSE_API UTDDamageHeroCalculation : public UGameplayEffectExecutionCalculation
{
    GENERATED_BODY()

public:

    UTDDamageHeroCalculation();

public:

protected:

private:

    TDAttributeCaptureDamageHero structAbilities;

public:

protected:

    virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;


private:
};
