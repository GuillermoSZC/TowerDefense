// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TDElementVFXDataAsset.generated.h"

/**
 *
 */

UENUM(BlueprintType)
enum EffectType 
{
    AttackSword,
    StaticSword,
    HitEnemy,
    TrailSword
};



class UNiagaraSystem;

UCLASS(BlueprintType,Blueprintable)
class TOWERDEFENSE_API UTDElementVFXDataAsset : public UDataAsset
{
    GENERATED_BODY()


public:

 
    UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
        TObjectPtr<UNiagaraSystem> AttackSwordEffect;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
        TObjectPtr<UNiagaraSystem> StaticSwordEffect;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
        TObjectPtr<UNiagaraSystem> HitEnemySwordEffect;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
        TObjectPtr<UNiagaraSystem> TrailSwordEffect;

public:

    //UFUNCTION(BlueprintPure)
    TObjectPtr<UNiagaraSystem> TDGetVFXType(EffectType _effect);

};
