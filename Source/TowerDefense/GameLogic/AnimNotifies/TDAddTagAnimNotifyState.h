// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include <GameplayTagContainer.h>
#include "TDAddTagAnimNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UTDAddTagAnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()
	


	private:
	UPROPERTY(EditAnywhere, meta = (DisplayName = "GameplayTag"))
		FGameplayTag notifiedTag;

public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration);
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation);
};

