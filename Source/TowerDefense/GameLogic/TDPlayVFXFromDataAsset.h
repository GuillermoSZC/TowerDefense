// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimNotify_PlayNiagaraEffect.h"
#include "TDPlayVFXFromDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UTDPlayVFXFromDataAsset : public UAnimNotify_PlayNiagaraEffect
{
	GENERATED_BODY()
	
public:
	void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

};
