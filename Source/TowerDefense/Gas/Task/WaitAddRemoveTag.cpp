// Fill out your copyright notice in the Description page of Project Settings.


#include "Gas/Task/WaitAddRemoveTag.h"
#include "AbilitySystemComponent.h"
#include "TickDuringTag.h"

UWaitAddRemoveTag::UWaitAddRemoveTag()
{
    bTickingTask = false;
    RegisteredCallback = false;
    OnlyTriggerOnce = false;
    hasTag = false;

}


UWaitAddRemoveTag* UWaitAddRemoveTag::WaitAddRemoveTag(UGameplayAbility* OwningAbility, FGameplayTag _Tag, bool _OnlyTriggerOnce /*= true*/)
{
    UWaitAddRemoveTag* delegateTask = NewAbilityTask<UWaitAddRemoveTag>(OwningAbility);

    delegateTask->mTag = _Tag;
    delegateTask->OnlyTriggerOnce = _OnlyTriggerOnce;

    return delegateTask;
}


UAbilitySystemComponent* UWaitAddRemoveTag::GetTargetASC()
{
    return AbilitySystemComponent.Get();
}


void UWaitAddRemoveTag::GameplayTagCallback(const FGameplayTag Tag, int32 NewCount)
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

void UWaitAddRemoveTag::Activate()
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

void UWaitAddRemoveTag::OnDestroy(bool AbilityIsEnding)
{
    UAbilitySystemComponent* ASC = GetTargetASC();
    if (RegisteredCallback && ASC)
    {
        ASC->RegisterGameplayTagEvent(mTag).Remove(DelegateHandle);
    }

    Super::OnDestroy(AbilityIsEnding);
}