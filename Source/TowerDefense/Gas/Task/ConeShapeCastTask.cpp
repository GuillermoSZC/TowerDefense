// Fill out your copyright notice in the Description page of Project Settings.


#include "Gas/Task/ConeShapeCastTask.h"
#include "DrawDebugHelpers.h"


UConeShapeCastTask::UConeShapeCastTask()
{

}

UConeShapeCastTask* UConeShapeCastTask::TDConeCheckInside(UGameplayAbility* OwningAbility, FVector _castPosition, FVector _direction, const TArray<AActor*>& _ActorsToCheck, float _coneAngle, float _distance)
{

    UConeShapeCastTask* MyObj = NewAbilityTask<UConeShapeCastTask>(OwningAbility);

    MyObj->Pos = _castPosition;
    MyObj->Dir = _direction;
    MyObj->actorsToCheck = _ActorsToCheck;
    MyObj->coneAngle = _coneAngle;
    MyObj->distance = _distance;

    return MyObj;

}

void UConeShapeCastTask::Activate()
{

    FVector Pos2D = Pos;
    Pos2D.Z = 0;

    for (AActor* iter : actorsToCheck)
    {


        FVector iterLocation = iter->GetActorLocation();
        FVector iterLocation2D = iterLocation;
        iterLocation2D.Z = 0;


        FVector directionIter = iterLocation2D - Pos2D;



        FVector NormalizeDirectionIter = directionIter.GetSafeNormal();
        float dotValue = FVector::DotProduct(Dir, NormalizeDirectionIter);
        float anglePos = FMath::RadiansToDegrees(FMath::Acos(dotValue));

        if (anglePos > coneAngle)
        {
            continue;
        }

        float distSquared = FVector::DistSquared2D(Pos, iterLocation);

        float distanceSquared = distance * distance;

        if (distSquared >= distanceSquared)
        {
            continue;
        }

        if (actorsInside.Contains(iter))
        {
            continue;
        }

        actorsInside.Add(iter);
    }


    hit.Broadcast(actorsInside);


    AActor* owner = GetAvatarActor();


    if (ITDInterface::Execute_TDIsDebugActive(owner))
    {
        UWorld* world = owner->GetWorld();


        FRotator rightRotator = FRotator(0.f, coneAngle, 0.f);
        FVector rightAngleVector = rightRotator.RotateVector(Dir);

        FRotator leftRotator = FRotator(0.f, -coneAngle, 0.f);
        FVector leftAngleVector = leftRotator.RotateVector(Dir);

        DrawDebugLine(world, Pos, Pos + rightAngleVector * distance, FColor::Orange, false, 1.5f, 0, 15.f);
        DrawDebugLine(world, Pos, Pos + leftAngleVector * distance, FColor::Orange, false, 1.5f, 0, 15.f);
        DrawDebugLine(world, Pos + rightAngleVector * distance, Pos + leftAngleVector * distance, FColor::Orange, false, 1.5f, 0, 15.f);




    }



}
