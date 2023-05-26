// Fill out your copyright notice in the Description page of Project Settings.


#include "Gas/Calculations/TDPlasmaHeal.h"

UTDPlasmaHeal::UTDPlasmaHeal()
{
    RelevantAttributesToCapture.Add(structAbilities.healthTargetDef);
    RelevantAttributesToCapture.Add(structAbilities.attackDamageSourceDef);
    RelevantAttributesToCapture.Add(structAbilities.levelSourceDef);
    valueMultiplier = 0.001f;

}

void UTDPlasmaHeal::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
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


        float playerHealth = 0.f;
        ensure(ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(structAbilities.healthTargetDef, evaluationParameters, playerHealth));

        float actualLevel = 0.f;
        ensure(ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(structAbilities.levelSourceDef, evaluationParameters, actualLevel));



        //cambiar actual Round por el nivel de la torre
        float TotalHealth = valueMultiplier * baseDamage * actualLevel;


        FGameplayModifierEvaluatedData TargetHealthModification = FGameplayModifierEvaluatedData(structAbilities.healthTargetProperty, EGameplayModOp::Additive, TotalHealth);
        OutExecutionOutput.AddOutputModifier(TargetHealthModification);
    }
}
