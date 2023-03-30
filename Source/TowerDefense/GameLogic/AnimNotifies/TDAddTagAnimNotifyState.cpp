// Fill out your copyright notice in the Description page of Project Settings.


#include "GameLogic/AnimNotifies/TDAddTagAnimNotifyState.h"

void UTDAddTagAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	UWorld* affectedWorld = MeshComp->GetWorld();
	if (affectedWorld) 
	{
		ATDCharacter* abilityCharacter = Cast<ATDCharacter>(MeshComp->GetOwner());

		if (abilityCharacter)
		{
			abilityCharacter->abilitySystem->AddLooseGameplayTag(notifiedTag);
		}
	}
}

void UTDAddTagAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	UWorld* affectedWorld = MeshComp->GetWorld();
	if (affectedWorld) 
	{
		ATDCharacter* abilityCharacter = Cast<ATDCharacter>(MeshComp->GetOwner());

		if (abilityCharacter)
		{
			abilityCharacter->abilitySystem->RemoveLooseGameplayTag(notifiedTag);
		}
	}
}
