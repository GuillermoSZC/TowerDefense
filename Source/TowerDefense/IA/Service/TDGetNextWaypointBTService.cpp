// Fill out your copyright notice in the Description page of Project Settings.


#include "IA/Service/TDGetNextWaypointBTService.h"
#include "Character/TDEnemy.h"
#include "GameLogic/TDPathPoint.h"
#include "Character/TDEnemyController.h"
#include "AIModule/Classes/BehaviorTree/BlackboardComponent.h"


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

                pathPoint->TDArrivedAction(enemyController);



            }
        }
    }



}
