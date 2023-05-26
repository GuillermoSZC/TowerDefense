// Fill out your copyright notice in the Description page of Project Settings.


#include "GameLogic/TDPlayVFXFromDataAsset.h"
#include "TDElementVFXDataAsset.h"
#include "Character/TDPlayerCharacter.h"
#include "TDGameData.h"
#include "Particles/ParticleSystemComponent.h"




UFXSystemComponent* UTDPlayVFXFromDataAsset::SpawnEffect(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    if (SpawnedEffect && IsValid(SpawnedEffect))
    {
        SpawnedEffect->Deactivate();
        SpawnedEffect->ConditionalBeginDestroy();
    }

    if (UTDGameData::TDGetPlayerRef() && UTDGameData::TDGetPlayerRef()->TDGetActualElementVFXAsset() && UTDGameData::TDGetPlayerRef()->TDGetActualElementVFXAsset()->TDGetVFXType(VFXtype))
    {
        if (Template != UTDGameData::TDGetPlayerRef()->TDGetActualElementVFXAsset()->TDGetVFXType(VFXtype))
        {
            Template = UTDGameData::TDGetPlayerRef()->TDGetActualElementVFXAsset()->TDGetVFXType(VFXtype);
            Super::SpawnEffect(MeshComp, Animation);
        }
    }
    else
    {
        Template = nullptr;
    }

  

    return SpawnedEffect;
}
