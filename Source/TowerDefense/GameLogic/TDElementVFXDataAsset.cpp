// Fill out your copyright notice in the Description page of Project Settings.


#include "GameLogic/TDElementVFXDataAsset.h"






TObjectPtr<UNiagaraSystem> UTDElementVFXDataAsset::TDGetVFXType(EffectType _effect)
{
    switch (_effect)
    {
    case EffectType::AttackSword:
    {
        return AttackSwordEffect;
    }
    break;

    case EffectType::HitEnemy:
    {
        return HitEnemySwordEffect;
    }
    break;

    case EffectType::StaticSword:
    {
        return StaticSwordEffect;
    }
    break;

    case EffectType::TrailSword:
    {
        return TrailSwordEffect;
    }
    break;  

    }
    return nullptr;
}
