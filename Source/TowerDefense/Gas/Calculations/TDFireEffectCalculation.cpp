// Fill out your copyright notice in the Description page of Project Settings.


#include "Gas/Calculations/TDFireEffectCalculation.h"

UTDFireEffectCalculation::UTDFireEffectCalculation()
{
    RelevantAttributesToCapture.Add(structAbilities.healthTargetDef);
    RelevantAttributesToCapture.Add(structAbilities.attackDamageSourceDef);
    RelevantAttributesToCapture.Add(structAbilities.levelSourceDef);
    valueMultiplier = 0.001f;
}

void UTDFireEffectCalculation::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
    FGameplayEffectSpec spec = ExecutionParams.GetOwningSpec();

    UAbilitySystemComponent* targetAbilitySystem = ExecutionParams.GetTargetAbilitySystemComponent();
    UAbilitySystemComponent* sourceAbilitySystem = ExecutionParams.GetSourceAbilitySystemComponent();

    AActor* targetActor = targetAbilitySystem->GetOwnerActor();
    AActor* sourceActor = sourceAbilitySystem->GetOwnerActor();

    if (targetActor && sourceActor)
    {

        FAggregatorEvaluateParameters evaluationParameters;

        float baseDamage = 0.f;
        ensure(ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(structAbilities.attackDamageSourceDef, evaluationParameters, baseDamage));


        float enemyHealth = 0.f;
        ensure(ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(structAbilities.healthTargetDef, evaluationParameters, enemyHealth));

        float actualLevel = 0.f;
        ensure(ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(structAbilities.levelSourceDef, evaluationParameters, actualLevel));



        //cambiar actual Round por el nivel de la torre
        float totalDamage = valueMultiplier * actualLevel * baseDamage;


        FGameplayModifierEvaluatedData TargetHealthModification = FGameplayModifierEvaluatedData(structAbilities.healthTargetProperty, EGameplayModOp::Additive, -totalDamage);
        OutExecutionOutput.AddOutputModifier(TargetHealthModification);
    }

}
