// Fill out your copyright notice in the Description page of Project Settings.


#include "DelegateTickTask.h"

UDelegateTickTask::UDelegateTickTask()
{
	bTickingTask = true;
}

UDelegateTickTask* UDelegateTickTask::DelegateTemporalTask(UGameplayAbility* OwningAbility, float _delegateDuration, float _delegateCallFrecuency)
{
	UDelegateTickTask* delegateTask = NewAbilityTask<UDelegateTickTask>(OwningAbility);
	delegateTask->delegateDuration = _delegateDuration;
	delegateTask->delegateCallFrecuency = _delegateCallFrecuency;

	return delegateTask;
}

void UDelegateTickTask::Activate()
{
	elapsedDelegateTime = 0.f;
	delegateFrecuencyElapsed = 0.f;
	onStart.Broadcast();
}

void UDelegateTickTask::TickTask(float DeltaTime)
{

	if (elapsedDelegateTime < delegateDuration)
	{
		delegateFrecuencyElapsed += DeltaTime;
		elapsedDelegateTime += DeltaTime;

		if (delegateFrecuencyElapsed > delegateCallFrecuency)
		{
			delegateFrecuencyElapsed = delegateFrecuencyElapsed - delegateCallFrecuency;
			delegateFunctionality.Broadcast(elapsedDelegateTime,DeltaTime);
		}
	}
	else 
	{
		onEnd.Broadcast();
		EndTask();
	}

}
