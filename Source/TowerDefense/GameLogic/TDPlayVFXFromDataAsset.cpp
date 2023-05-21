// Fill out your copyright notice in the Description page of Project Settings.


#include "GameLogic/TDPlayVFXFromDataAsset.h"
#include "TDElementVFXDataAsset.h"
#include "Character/TDPlayerCharacter.h"
#include "TDGameData.h"
#include "Particles/ParticleSystemComponent.h"


void UTDPlayVFXFromDataAsset::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{

    if (UTDGameData::TDGetPlayerRef() && UTDGameData::TDGetPlayerRef()->TDGetActualElementVFXAsset() && UTDGameData::TDGetPlayerRef()->TDGetActualElementVFXAsset()->HitSwordEffect)
    {
        if(Template != UTDGameData::TDGetPlayerRef()->TDGetActualElementVFXAsset()->HitSwordEffect)
        {
            if (IsValid(SpawnedEffect))
            {
                //SpawnedEffect->
                //SpawnedEffect->DeactivateImmediate();
                //SpawnedEffect->ConditionalBeginDestroy();
                //SpawnedEffect = nullptr;
            }       
            Template = UTDGameData::TDGetPlayerRef()->TDGetActualElementVFXAsset()->HitSwordEffect;
        }
    }



    Super::Notify(MeshComp, Animation, EventReference);
}
