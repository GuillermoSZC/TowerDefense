// Fill out your copyright notice in the Description page of Project Settings.


#include "Gas/Calculations/TDDamageHeroCalculation.h"
#include "GameplayEffectExecutionCalculation.h"
#include "GameLogic/TDElementComponent.h"
#include "Interfaces/TDInterface.h"



UTDDamageHeroCalculation::UTDDamageHeroCalculation()
{
    RelevantAttributesToCapture.Add(structAbilities.healthTargetDef);
    RelevantAttributesToCapture.Add(structAbilities.attackDamageSourceDef);
    RelevantAttributesToCapture.Add(structAbilities.DamageLevelSourceDef);
}


void UTDDamageHeroCalculation::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{

    FGameplayEffectSpec spec = ExecutionParams.GetOwningSpec();

    UAbilitySystemComponent* targetAbilitySystem = ExecutionParams.GetTargetAbilitySystemComponent();
    UAbilitySystemComponent* sourceAbilitySystem = ExecutionParams.GetSourceAbilitySystemComponent();

    AActor* targetActor = targetAbilitySystem->GetOwnerActor();
    AActor* sourceActor = sourceAbilitySystem->GetOwnerActor();

    if (targetActor && sourceActor)
    {

        if (targetAbilitySystem->HasMatchingGameplayTag(GET_GAMEPLAY_TAG(INMORTAL_STATE_TAG)))
        {
            return;
        }


        FAggregatorEvaluateParameters evaluationParameters;

        float baseDamage = 0.f;
        ensure(ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(structAbilities.attackDamageSourceDef, evaluationParameters, baseDamage));


        float enemyHealth = 0.f;
        ensure(ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(structAbilities.healthTargetDef, evaluationParameters, enemyHealth));

        float level = 0.f;
        ensure(ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(structAbilities.DamageLevelSourceDef, evaluationParameters, level));

        UTDElementComponent* SourceElementComponent = ITDInterface::Execute_TDGetElementComponent(sourceActor);
        UTDElementComponent* TargetElementComponent = ITDInterface::Execute_TDGetElementComponent(targetActor);
       
        float elementMultiplier = SourceElementComponent->TDGetDamageMultiplier(TargetElementComponent->TDGetOwnerElement());


        float TotalDamage = elementMultiplier * baseDamage * (1 + (0.1f * level));



        FGameplayModifierEvaluatedData TargetHealthModification = FGameplayModifierEvaluatedData(structAbilities.healthTargetProperty, EGameplayModOp::Additive, -TotalDamage);
        OutExecutionOutput.AddOutputModifier(TargetHealthModification);

    }

}

