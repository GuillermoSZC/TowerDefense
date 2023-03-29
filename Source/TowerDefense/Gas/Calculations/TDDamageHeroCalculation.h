// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "TDMacros.h"
#include "Map/TDTowerAttributeSet.h"
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
        TDDEFINE_ATTRIBUTE_CAPTUREDEF(UTDCharacterAttributeSet, health, Target, false);
        TDDEFINE_ATTRIBUTE_CAPTUREDEF(UTDCharacterAttributeSet, attackDamage, Source, false);
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
