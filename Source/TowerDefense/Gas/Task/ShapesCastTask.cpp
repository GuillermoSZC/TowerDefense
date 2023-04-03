// Fill out your copyright notice in the Description page of Project Settings.


#include "Gas/Task/ShapesCastTask.h"
#include "DrawDebugHelpers.h"
#include "Engine/Private/KismetTraceUtils.h"

UShapesCastTask::UShapesCastTask()
{

}

UShapesCastTask* UShapesCastTask::TDBoxShapeCast(UGameplayAbility* OwningAbility, FVector castPosition, FRotator rotator, FVector boxSize, const TArray<TEnumAsByte<EObjectTypeQuery>>& ObjectTypes)
{
    UShapesCastTask* MyObj = NewAbilityTask<UShapesCastTask>(OwningAbility);



    MyObj->pos = castPosition;
    MyObj->rotation = rotator;
    MyObj->boxSize = boxSize;
    //MyObj->objectchannel = _traceChannel;
    MyObj->shape = shapeType::box;
    MyObj->objectchannel = FCollisionObjectQueryParams(ObjectTypes);

    //MyObj->objectchannel = ConfigureCollisionObjectParams(ObjectTypes);
    return MyObj;
}

UShapesCastTask* UShapesCastTask::TDSphereShapeCast(UGameplayAbility* OwningAbility, FVector castPosition, FRotator rotator, float _radius, const TArray<TEnumAsByte<EObjectTypeQuery>>& ObjectTypes)
{

    UShapesCastTask* MyObj = NewAbilityTask<UShapesCastTask>(OwningAbility);

    MyObj->pos = castPosition;
    MyObj->rotation = rotator;
    MyObj->radius = _radius;
    //MyObj->objectchannel = _traceChannel;
    MyObj->shape = shapeType::spehere;
    MyObj->objectchannel = FCollisionObjectQueryParams(ObjectTypes);


    //MyObj->objectchannel = ConfigureCollisionObjectParams(ObjectTypes);
    return MyObj;
}

UShapesCastTask* UShapesCastTask::TDCapsuleShapeCast(UGameplayAbility* OwningAbility, FVector castPosition, FRotator rotator, float height, float _radius, const TArray<TEnumAsByte<EObjectTypeQuery>>& ObjectTypes)
{
    UShapesCastTask* MyObj = NewAbilityTask<UShapesCastTask>(OwningAbility);


    MyObj->pos = castPosition;
    MyObj->rotation = rotator;
    MyObj->radius = _radius;
    MyObj->height = height;
    //MyObj->objectchannel = _traceChannel;
    MyObj->shape = shapeType::capsule;
    MyObj->objectchannel = FCollisionObjectQueryParams(ObjectTypes);

    //MyObj->objectchannel = ConfigureCollisionObjectParams(ObjectTypes);
    return MyObj;
}

void UShapesCastTask::Activate()
{
    Super::Activate();

    bool hitted = false;

    switch (shape)
    {
    case shapeType::capsule:
    {
        hitted = GetWorld()->SweepMultiByObjectType(hitResultArray, pos, pos, rotation.Quaternion(), objectchannel, FCollisionShape::MakeCapsule(radius, height));

        if (ITDInterface::Execute_TDIsDebugActive(GetAvatarActor()))
        {
            DrawDebugCapsule(GetWorld(), pos, height, radius, rotation.Quaternion(), FColor::Orange, false, 0.f, 0, 5.f);

        }


    }
    break;

    case shapeType::box:
    {

        hitted = GetWorld()->SweepMultiByObjectType(hitResultArray, pos, pos, rotation.Quaternion(), objectchannel, FCollisionShape::MakeBox(boxSize));
        if (ITDInterface::Execute_TDIsDebugActive(GetAvatarActor()))
        {
            DrawDebugBox(GetWorld(), pos, boxSize, rotation.Quaternion(), FColor::Orange, false, 0.f, 0, 5.f);

        }

    }
    break;


    case shapeType::spehere:
    {
        //hitted = GetWorld()->SweepMultiByChannel(hitResultArray, pos, pos, rotation.Quaternion(), TraceChannel, );
        hitted = GetWorld()->SweepMultiByObjectType(hitResultArray, pos, pos, rotation.Quaternion(), objectchannel, FCollisionShape::MakeSphere(radius));
        if (ITDInterface::Execute_TDIsDebugActive(GetAvatarActor()))
        {
            DrawDebugSphere(GetWorld(), pos, radius, 32, FColor::Orange, false, 0.f, 0, 5.f);
        }

    }
    break;

    case shapeType::none:
    {

    }
    break;
    default:
        break;
    }

    if (hitted)
    {
        for (FHitResult Iter : hitResultArray)
        {
            hittedActors.Add(Iter.GetActor());
            hit.Broadcast(hittedActors, hitResultArray);
        }
    }
    else
    {
        nohit.Broadcast();
    }

}
