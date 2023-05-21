// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimNotify_PlayNiagaraEffect.h"
#include "TDElementVFXDataAsset.h"
#include "TDPlayVFXFromDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UTDPlayVFXFromDataAsset : public UAnimNotify_PlayNiagaraEffect
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	TEnumAsByte<EffectType> VFXtype;

protected:
	UFXSystemComponent* SpawnEffect(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

};
