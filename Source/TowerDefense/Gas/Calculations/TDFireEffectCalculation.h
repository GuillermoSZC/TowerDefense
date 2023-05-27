// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "TDFireEffectCalculation.generated.h"



struct TDAttributeCaptureFireEffect
{
    TDDECLARE_ATTRIBUTE_CAPTUREDEF(health, Target);
    TDDECLARE_ATTRIBUTE_CAPTUREDEF(attackDamage, Source);
    TDDECLARE_ATTRIBUTE_CAPTUREDEF(level, Source);

    TDAttributeCaptureFireEffect()
    {
        TDDEFINE_ATTRIBUTE_CAPTUREDEF(UTDHealthAttributeSet, health, Target, false);
        TDDEFINE_ATTRIBUTE_CAPTUREDEF(UTDDamageAttributeSet, attackDamage, Source, false);
        TDDEFINE_ATTRIBUTE_CAPTUREDEF(UTDLevelAttributeSet, level, Source, false);
    }
};




UCLASS()
class TOWERDEFENSE_API UTDFireEffectCalculation : public UGameplayEffectExecutionCalculation
{
    GENERATED_BODY()


public:

        UTDFireEffectCalculation();

public:

    UPROPERTY(EditAnywhere,BlueprintReadWrite)
    float valueMultiplier;

protected:

private:

    TDAttributeCaptureFireEffect structAbilities;

public:

protected:

    virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;


private:



};
