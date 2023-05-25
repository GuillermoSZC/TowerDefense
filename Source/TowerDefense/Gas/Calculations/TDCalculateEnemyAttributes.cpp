// Fill out your copyright notice in the Description page of Project Settings.


#include "Gas/Calculations/TDCalculateEnemyAttributes.h"



UTDCalculateEnemyAttributes::UTDCalculateEnemyAttributes()
{

    RelevantAttributesToCapture.Add(structAbilities.maxHealthTargetDef);
    RelevantAttributesToCapture.Add(structAbilities.healthTargetDef);
    RelevantAttributesToCapture.Add(structAbilities.attackDamageTargetDef);
    RelevantAttributesToCapture.Add(structAbilities.attackSpeedTargetDef);
    RelevantAttributesToCapture.Add(structAbilities.attackRangeTargetDef);
    RelevantAttributesToCapture.Add(structAbilities.movementSpeedTargetDef);

}


void UTDCalculateEnemyAttributes::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{

    FGameplayEffectSpec spec = ExecutionParams.GetOwningSpec();

    UAbilitySystemComponent* targetAbilitySystem = ExecutionParams.GetTargetAbilitySystemComponent();



}