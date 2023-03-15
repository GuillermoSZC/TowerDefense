// Fill out your copyright notice in the Description page of Project Settings.


#include "Gas/Task/ConeShapeCastTask.h"


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
            break;
        }

        float distSquared = FVector::DistSquared2D(Pos, iterLocation);

        float distanceSquared = distance * distance;

        if (distSquared >= distance)
        {
            break;
        }

        if (actorsInside.Contains(iter))
        {
            break;
        }

        actorsInside.Add(iter);        
    }


    hit.Broadcast(actorsInside);

}
