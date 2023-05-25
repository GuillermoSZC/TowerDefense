// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "TDMacros.h"
#include "AttributesSets/TDHealthAttributeSet.h"
#include "AttributesSets/TDDamageAttributeSet.h"
#include "AttributesSets/TDMovementAttributeSet.h"
#include "TDCalculateEnemyAttributes.generated.h"

/**
 * 
 */

struct TDAtrributeCaptureEnemy
{
	TDDECLARE_ATTRIBUTE_CAPTUREDEF(maxHealth, Target);
	TDDECLARE_ATTRIBUTE_CAPTUREDEF(health, Target);
	TDDECLARE_ATTRIBUTE_CAPTUREDEF(attackDamage, Target);
	TDDECLARE_ATTRIBUTE_CAPTUREDEF(attackSpeed, Target);
	TDDECLARE_ATTRIBUTE_CAPTUREDEF(attackRange, Target);
	TDDECLARE_ATTRIBUTE_CAPTUREDEF(movementSpeed, Target);


	TDAtrributeCaptureEnemy()
	{
		TDDEFINE_ATTRIBUTE_CAPTUREDEF(UTDHealthAttributeSet, maxHealth, Target, false);
		TDDEFINE_ATTRIBUTE_CAPTUREDEF(UTDHealthAttributeSet, health, Target, false);
		TDDEFINE_ATTRIBUTE_CAPTUREDEF(UTDDamageAttributeSet, attackDamage, Target, false);
		TDDEFINE_ATTRIBUTE_CAPTUREDEF(UTDDamageAttributeSet, attackSpeed, Target, false);
		TDDEFINE_ATTRIBUTE_CAPTUREDEF(UTDDamageAttributeSet, attackRange, Target, false);
		TDDEFINE_ATTRIBUTE_CAPTUREDEF(UTDMovementAttributeSet, movementSpeed, Target, false);

	}


};


UCLASS()
class TOWERDEFENSE_API UTDCalculateEnemyAttributes : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
	
public:

	UTDCalculateEnemyAttributes();

public:

	UPROPERTY(EditAnywhere, Category = "")
	float healthBaseValue;

	UPROPERTY(EditAnywhere)
	float healthRoundMultiplier;

	UPROPERTY(EditAnywhere)
	float AttackDamageBaseValue;

	UPROPERTY(EditAnywhere)
	float AttackDamageRoundMultiplier;

	UPROPERTY(EditAnywhere)
	float AttackSpeedBaseValue;

	UPROPERTY(EditAnywhere)
	float AttackRangeBaseValue;

	UPROPERTY(EditAnywhere)
	float SpeedBaseValue;


protected:

private:

	TDAtrributeCaptureEnemy structAbilities;

public:

protected:

	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;

private:



};
