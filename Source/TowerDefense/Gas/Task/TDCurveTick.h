// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "Delegates/TDDeclareDelegates.h"
#include "TDCurveTick.generated.h"

class UCurveFloat;

/**
 *
 */
UCLASS()
class TOWERDEFENSE_API UTDCurveTick : public UAbilityTask
{
    GENERATED_BODY()

public:

    UTDCurveTick();

public:

protected:
    UPROPERTY(BlueprintAssignable)
        FCurveTickSignature FCurveTickSignatureDelegate;

    UPROPERTY(BlueprintAssignable)
        FEndDelegateTickTask FEndDelegateTickTaskDelegate;

private:
    UPROPERTY(Transient)
        UCurveFloat* curve;

    FAlphaBlend timeline;

public:
    UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
        static UTDCurveTick* TDTickDuringCurve(UGameplayAbility* OwningAbility, UCurveFloat* _curve);

    void TickTask(float DeltaTime) override;

protected:

    void Activate() override;

private:


};
