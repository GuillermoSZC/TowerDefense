// Fill out your copyright notice in the Description page of Project Settings.


#include "Gas/Calculations/TDDamageTowerCalculation.h"
#include "GameplayEffectExecutionCalculation.h"



UTDDamageTowerCalculation::UTDDamageTowerCalculation()
{
    RelevantAttributesToCapture.Add(structAbilities.healthTargetDef);
    RelevantAttributesToCapture.Add(structAbilities.attackDamageSourceDef);
}


void UTDDamageTowerCalculation::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
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

        int32 actualRound = UTDGameData::TDGetRoundManager()->TDGetActualRound();

        UTDElementComponent* SourceElementComponent = ITDInterface::Execute_TDGetElementComponent(sourceActor);
        UTDElementComponent* TargetElementComponent = ITDInterface::Execute_TDGetElementComponent(targetActor);
       
        float elementMultiplier = SourceElementComponent->TDGetDamageMultiplier(TargetElementComponent->TDGetOwnerElement());


        //cambiar actual Round por el nivel de la torre
        float TotalDamage = elementMultiplier * baseDamage * (1 + (0.1f * actualRound));


        FGameplayModifierEvaluatedData TargetHealthModification = FGameplayModifierEvaluatedData(structAbilities.healthTargetProperty, EGameplayModOp::Additive, -TotalDamage);
        OutExecutionOutput.AddOutputModifier(TargetHealthModification);

    }

}

