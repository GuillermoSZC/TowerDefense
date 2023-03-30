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


UAbilitySystemComponent* UTickDuringTag::GetTargetASC()
{
    return AbilitySystemComponent.Get();
}


void UTickDuringTag::GameplayTagCallback(const FGameplayTag Tag, int32 NewCount)
{
    if (NewCount == 1)
    {
        if (ShouldBroadcastAbilityTaskDelegates())
        {
            hasTag = true;
            Added.Broadcast();
        }
    }

    if (NewCount == 0)
    {
        if (ShouldBroadcastAbilityTaskDelegates())
        {
           
            Removed.Broadcast();
        }

        if (OnlyTriggerOnce && hasTag == true)
        {
            hasTag = false;
            EndTask();
        }
        else
        {
            hasTag = false;
        }
    }



}

void UTickDuringTag::Activate()
{
    UAbilitySystemComponent* ASC = GetTargetASC();

    if (ASC && ASC->HasMatchingGameplayTag(mTag))
    {
        if (ShouldBroadcastAbilityTaskDelegates())
        {
            hasTag = true;
            Added.Broadcast();
        }
    }

    if (ASC)
    {
        DelegateHandle = ASC->RegisterGameplayTagEvent(mTag).AddUObject(this, &UTickDuringTag::GameplayTagCallback);
        RegisteredCallback = true;

    }
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


void UTickDuringTag::OnDestroy(bool AbilityIsEnding)
{
    UAbilitySystemComponent* ASC = GetTargetASC();
    if (RegisteredCallback && ASC)
    {
        ASC->RegisterGameplayTagEvent(mTag).Remove(DelegateHandle);
    }

    Super::OnDestroy(AbilityIsEnding);
}