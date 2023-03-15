// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "ConeShapeCastTask.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FConeArrayDelegate, const TArray<AActor*>&, ActorsArray);


/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UConeShapeCastTask : public UAbilityTask
{
	GENERATED_BODY()
	
public:

	UConeShapeCastTask();

public:


    UPROPERTY(BlueprintAssignable)
		FConeArrayDelegate hit;

protected:

private:

	FVector Pos;
	FVector Dir;
	TArray<AActor*> actorsToCheck;
	float coneAngle;
	float distance;
	TArray<AActor*> actorsInside;


public:


    UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
        static UConeShapeCastTask* TDConeCheckInside(UGameplayAbility* OwningAbility, FVector _castPosition, FVector _direction, const TArray<AActor*>& _ActorsToCheck, float _coneAngle, float _distance);

protected:

private:


    virtual void Activate() override;


};
