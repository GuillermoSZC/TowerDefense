// Fill out your copyright notice in the Description page of Project Settings.


#include "IA/Service/TDGetNextWaypointBTService.h"
#include "Character/TDEnemy.h"
#include "GameLogic/TDPathPoint.h"
#include "Character/TDEnemyController.h"
#include "AIModule/Classes/BehaviorTree/BlackboardComponent.h"
#include "Map/TDBase.h"
#include "GameLogic/TDGameData.h"


UTDGetNextWaypointBTService::UTDGetNextWaypointBTService()
{

}

void UTDGetNextWaypointBTService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);


    ATDEnemyController* enemyController = Cast<ATDEnemyController>(OwnerComp.GetOwner());
    ATDEnemy* enemy = enemyController->GetPawn<ATDEnemy>();
    UBlackboardComponent* blackboard = OwnerComp.GetBlackboardComponent();

    if (blackboard)
    {

        UObject* waypointObject;
        ATDPathPoint* pathPoint;

        waypointObject = blackboard->GetValueAsObject(FName(TEXT("WaypointActor")));
        pathPoint = Cast<ATDPathPoint>(waypointObject);


        if (pathPoint && enemy)
        {
            FVector enemyPos = enemy->GetActorLocation();
            FVector PatrolPoint = pathPoint->GetActorLocation();

            float distanceBt = FVector::DistSquared2D(enemyPos, PatrolPoint);
            if (distanceBt <= ArriveDistance)
            {

               // pathPoint->TDArrivedAction(enemyController);


                if (!pathPoint->TDGetIsBase())
                {
                    pathPoint = enemy->TDGetNextPathPoint();
                    blackboard->SetValueAsObject(FName(TEXT("WaypointActor")), pathPoint);
                    blackboard->SetValueAsVector(FName(TEXT("WaypointPosition")), pathPoint->GetActorLocation());
                }
                else
                {
                    ATDBase* baseRef = UTDGameData::TDGetBaseActor();
                    blackboard->SetValueAsObject(FName(TEXT("BaseBuild")), baseRef);
                    FVector basePos = baseRef->GetActorLocation();
                    //basePos.X = 930.f;
                    //basePos.Y = 210.f;
                    basePos.Z = 0.f;
                    blackboard->SetValueAsVector(FName(TEXT("BasePosition")), basePos);
                }

            }
        }
    }



}
