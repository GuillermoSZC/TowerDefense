// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "Gas/Task/WaitAddRemoveTag.h"
#include "DelegateTickTask.h"
#include "TickDuringTag.generated.h"



// DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTickSignatures, float, DeltaTime);




/**
 *
 */
UCLASS()
class TOWERDEFENSE_API UTickDuringTag : public UWaitAddRemoveTag
{
    GENERATED_BODY()

public:

    UTickDuringTag();



public:

protected:

private:



    float elapsedDelegateTime;
    float delegateCallFrecuency;
    float delegateFrecuencyElapsed;



      UPROPERTY(BlueprintAssignable)
        FTickSignature FTick;  

public:

    UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
        static UTickDuringTag* TickDuringTag(UGameplayAbility* OwningAbility, FGameplayTag _Tag,float _callFrequency, bool _OnlyTriggerOnce = true);

protected:



    void TickTask(float DeltaTime) override;

private:








};
