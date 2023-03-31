// Fill out your copyright notice in the Description page of Project Settings.


#include "Gas/Task/TickDuringTag.h"
#include "AbilitySystemComponent.h"

UTickDuringTag::UTickDuringTag()
{
    bTickingTask = true;
    RegisteredCallback = false;
    OnlyTriggerOnce = false;
    hasTag = false;

}


UTickDuringTag* UTickDuringTag::TickDuringTag(UGameplayAbility* OwningAbility, FGameplayTag _Tag,  float _callFrequency, bool _OnlyTriggerOnce /*= true*/)
{
    UTickDuringTag* delegateTask = NewAbilityTask<UTickDuringTag>(OwningAbility);

    delegateTask->mTag = _Tag;
    delegateTask->delegateCallFrecuency = _callFrequency;
    delegateTask->OnlyTriggerOnce = _OnlyTriggerOnce;

    return delegateTask;
}


void UTickDuringTag::TickTask(float DeltaTime)
{
    Super::TickTask(DeltaTime);

    if (hasTag)
    {
        delegateFrecuencyElapsed += DeltaTime;
        elapsedDelegateTime += DeltaTime;

        if (delegateFrecuencyElapsed > delegateCallFrecuency)
        {
            delegateFrecuencyElapsed = delegateFrecuencyElapsed - delegateCallFrecuency;

            FTick.Broadcast(elapsedDelegateTime,DeltaTime);
        }
    }
}


