// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TDElementVFXDataAsset.generated.h"

/**
 *
 */

class UNiagaraSystem;

UCLASS(BlueprintType,Blueprintable)
class TOWERDEFENSE_API UTDElementVFXDataAsset : public UDataAsset
{
    GENERATED_BODY()


public:

 


    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
        TObjectPtr<UNiagaraSystem> HitSwordEffect;


};
