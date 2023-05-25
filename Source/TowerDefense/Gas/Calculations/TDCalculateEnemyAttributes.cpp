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

    int round = UTDGameData::TDGetRoundManager()->TDGetActualRound();

    float newHealth = healthBaseValue + (healthRoundMultiplier * round);

    float newAttackSpeed = AttackSpeedBaseValue;

    float newAttackDamage = AttackDamageBaseValue + (AttackDamageRoundMultiplier * round);

    float newAttackRange = AttackRangeBaseValue;

    float newMoveSpeed = SpeedBaseValue;

    FGameplayModifierEvaluatedData TargetMaxHealthModification = FGameplayModifierEvaluatedData(structAbilities.maxHealthTargetProperty, EGameplayModOp::Override, newHealth);
    FGameplayModifierEvaluatedData TargetHealthModification = FGameplayModifierEvaluatedData(structAbilities.healthTargetProperty, EGameplayModOp::Override, newHealth);
    FGameplayModifierEvaluatedData TargetAttackSpeedModification = FGameplayModifierEvaluatedData(structAbilities.attackSpeedTargetProperty, EGameplayModOp::Override, newAttackSpeed);
    FGameplayModifierEvaluatedData TargetAttackDamageModification = FGameplayModifierEvaluatedData(structAbilities.attackDamageTargetProperty, EGameplayModOp::Override, newAttackDamage);
    FGameplayModifierEvaluatedData TargetAttackRangeModification = FGameplayModifierEvaluatedData(structAbilities.attackRangeTargetProperty, EGameplayModOp::Override, newAttackRange);
    FGameplayModifierEvaluatedData TargetSpeedModification = FGameplayModifierEvaluatedData(structAbilities.movementSpeedTargetProperty, EGameplayModOp::Override, newMoveSpeed);

    OutExecutionOutput.AddOutputModifier(TargetMaxHealthModification);
    OutExecutionOutput.AddOutputModifier(TargetHealthModification);
    OutExecutionOutput.AddOutputModifier(TargetAttackSpeedModification);
    OutExecutionOutput.AddOutputModifier(TargetAttackDamageModification);
    OutExecutionOutput.AddOutputModifier(TargetAttackRangeModification);
    OutExecutionOutput.AddOutputModifier(TargetSpeedModification);


}