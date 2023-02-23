// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "UObject/ObjectMacros.h"
#include "CollisionQueryParams.h"
#include "ShapesCastTask.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FArrayDelegate, const TArray<AActor*>&, ActorsArray, const TArray<FHitResult>&, HitResutlsArray);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEndDelegate);

enum shapeType
{
    none = 0,
    spehere = 1,
    box = 2,
    capsule = 3
};





UCLASS()
class TOWERDEFENSE_API UShapesCastTask : public UAbilityTask
{
    GENERATED_BODY()

public:

    UShapesCastTask();

public:

    UPROPERTY(BlueprintAssignable)
        FArrayDelegate hit;

    UPROPERTY(BlueprintAssignable)
        FEndDelegate nohit;


protected:

private:

    shapeType shape = shapeType::none;


    FVector pos;
    FRotator rotation;

    float radius;
    float height;

    FVector boxSize;

    //ECollisionChannel TraceChannel;
    FCollisionObjectQueryParams objectchannel;


    TArray<AActor*> hittedActors;
    TArray<FHitResult> hitResultArray;


public:


    UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
        static UShapesCastTask* TDBoxShapeCast(UGameplayAbility* OwningAbility, FVector castPosition, FRotator rotator, FVector boxSize, const TArray<TEnumAsByte<EObjectTypeQuery>>& ObjectTypes);

    UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
        static UShapesCastTask* TDSphereShapeCast(UGameplayAbility* OwningAbility, FVector castPosition, FRotator rotator, float _radius, const TArray<TEnumAsByte<EObjectTypeQuery>>& ObjectTypes);

    UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
        static UShapesCastTask* TDCapsuleShapeCast(UGameplayAbility* OwningAbility, FVector castPosition, FRotator rotator, float height, float _radius, const TArray<TEnumAsByte<EObjectTypeQuery>>& ObjectTypes);

protected:

private:


    virtual void Activate() override;

};
