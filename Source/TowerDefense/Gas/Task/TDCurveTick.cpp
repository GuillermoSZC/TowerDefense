    // Fill out your copyright notice in the Description page of Project Settings.


#include "Gas/Task/TDCurveTick.h"
#include "Curves/CurveFloat.h"

UTDCurveTick::UTDCurveTick()
{
    bTickingTask = true;
}

UTDCurveTick* UTDCurveTick::TDTickDuringCurve(UGameplayAbility* OwningAbility, UCurveFloat* _curve)
{
    UTDCurveTick* MyObj = NewAbilityTask<UTDCurveTick>(OwningAbility);

    MyObj->curve = _curve;
   
    return MyObj;
}

void UTDCurveTick::Activate()
{
    Super::Activate();
    float x, y;
    curve->GetTimeRange(x,y);
    timeline = FAlphaBlend(y);
    timeline.SetCustomCurve(curve);

}

void UTDCurveTick::TickTask(float DeltaTime)
{
    Super::TickTask(DeltaTime);

    timeline.Update(DeltaTime);

    FCurveTickSignatureDelegate.Broadcast(timeline.AlphaToBlendOption(timeline.GetAlpha(),EAlphaBlendOption::Custom,curve), DeltaTime);

    if (timeline.IsComplete())
    {
        FEndDelegateTickTaskDelegate.Broadcast();
        EndTask();
    }
}


