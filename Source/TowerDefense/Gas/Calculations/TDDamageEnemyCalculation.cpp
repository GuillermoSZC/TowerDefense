// Fill out your copyright notice in the Description page of Project Settings.


#include "Gas/Calculations/TDDamageEnemyCalculation.h"
#include "GameplayEffectExecutionCalculation.h"



UTDDamageEnemyCalculation::UTDDamageEnemyCalculation()
{
    RelevantAttributesToCapture.Add(structAbilities.healthTargetDef);
    RelevantAttributesToCapture.Add(structAbilities.attackDamageSourceDef);
    RelevantAttributesToCapture.Add(structAbilities.levelSourceDef);
}


void UTDDamageEnemyCalculation::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
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



        //         UTDElementComponent* SourceElementComponent = ITDInterface::Execute_TDGetElementComponent(sourceActor);
        //         UTDElementComponent* TargetElementComponent = ITDInterface::Execute_TDGetElementComponent(targetActor);
        //        
        //         float elementMultiplier = SourceElementComponent->TDGetDamageMultiplier(TargetElementComponent->TDGetOwnerElement());

        float wave = UTDGameData::TDGetRoundManager()->TDGetActualRound();


        float TotalDamage = baseDamage + (2 * wave);


        FGameplayModifierEvaluatedData TargetHealthModification = FGameplayModifierEvaluatedData(structAbilities.healthTargetProperty, EGameplayModOp::Additive, -TotalDamage);
        OutExecutionOutput.AddOutputModifier(TargetHealthModification);

    }

}

