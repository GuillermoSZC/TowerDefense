// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "TDMAgnitudeSlowCalculation.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UTDMAgnitudeSlowCalculation : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
	
public:

	UTDMAgnitudeSlowCalculation();

public:

	FGameplayEffectAttributeCaptureDefinition SourceLevel;



	UPROPERTY(EditDefaultsOnly)
	float IceSlowMultiplier = 0.01f;
protected:

private:

public:

	float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;


protected:

private:



};
