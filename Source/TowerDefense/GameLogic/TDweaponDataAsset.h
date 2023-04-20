// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TDweaponDataAsset.generated.h"

/**
 *
 */

UENUM()
enum AssetType 
{
    StaticMesh,
    SkeletalMesh,
    None   
};



UCLASS()
class TOWERDEFENSE_API UTDweaponDataAsset : public UDataAsset
{
    GENERATED_BODY()


public:


    void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;

public:


        UPROPERTY(EditAnywhere)
		TEnumAsByte<AssetType> assetClass;


    


    UPROPERTY(EditDefaultsOnly, meta = ( EditCondition = "assetClass==AssetType::SkeletalMesh", EditConditionHides))
        TSoftObjectPtr<USkeletalMesh> skeletalWeaponMesh;

       UPROPERTY(EditDefaultsOnly, meta = (EditCondition = "assetClass==AssetType::StaticMesh", EditConditionHides))
        TSoftObjectPtr<UStaticMesh> StaticWeaponMesh;



    UPROPERTY(EditDefaultsOnly)
        FName SocketName;

    UPROPERTY(EditDefaultsOnly)
        TSubclassOf<class UGameplayAbility> weaponAbility;


protected:

private:
    


public:

protected:

private:


};
