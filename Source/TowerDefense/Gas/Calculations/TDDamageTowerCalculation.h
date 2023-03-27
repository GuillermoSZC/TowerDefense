// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "TDMacros.h"
#include "Map/TDTowerAttributeSet.h"
#include "TDDamageTowerCalculation.generated.h"

/**
 *
 */

struct TDAttributeCaptureDamage
{
    TDDECLARE_ATTRIBUTE_CAPTUREDEF(health, Target);
    TDDECLARE_ATTRIBUTE_CAPTUREDEF(damage, Source);

    TDAttributeCaptureDamage()
    {
        TDDEFINE_ATTRIBUTE_CAPTUREDEF(UTDCharacterAttributeSet, health, Target, false);
        TDDEFINE_ATTRIBUTE_CAPTUREDEF(UTDTowerAttributeSet, damage, Source, false);
    }
};



UCLASS()
class TOWERDEFENSE_API UTDDamageTowerCalculation : public UGameplayEffectExecutionCalculation
{
    GENERATED_BODY()

public:

    UTDDamageTowerCalculation();

public:

protected:

private:

    TDAttributeCaptureDamage structAbilities;

public:

protected:

    virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;


private:
};
