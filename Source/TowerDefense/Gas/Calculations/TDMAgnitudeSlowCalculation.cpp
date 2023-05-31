// Fill out your copyright notice in the Description page of Project Settings.


#include "Gas/Calculations/TDMAgnitudeSlowCalculation.h"

UTDMAgnitudeSlowCalculation::UTDMAgnitudeSlowCalculation()
{
    SourceLevel.AttributeToCapture = UTDLevelAttributeSet::GetlevelAttribute();
    SourceLevel.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
    RelevantAttributesToCapture.Add(SourceLevel);
}

float UTDMAgnitudeSlowCalculation::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
    Super::CalculateBaseMagnitude_Implementation(Spec);


    const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
    const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

    FAggregatorEvaluateParameters EvaluationParameters;
    EvaluationParameters.SourceTags = SourceTags;
    EvaluationParameters.TargetTags = TargetTags;


    float level = 0.f;
    GetCapturedAttributeMagnitude(SourceLevel, Spec, EvaluationParameters, level);

    float iceslowValue = 0.9f - ((IceSlowMultiplier * level) / 2);

    return iceslowValue;

}
