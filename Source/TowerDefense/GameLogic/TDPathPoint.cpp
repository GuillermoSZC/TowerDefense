#include "GameLogic/TDPathPoint.h"
#include "Character/TDEnemyController.h"
#include "Character/TDEnemy.h"
#include "AIModule/Classes/BehaviorTree/BlackboardComponent.h"

ATDPathPoint::ATDPathPoint()
{
    
}

void ATDPathPoint::TDArrivedAction(ATDEnemyController* _enemy)
{
    if (!isBase)
    {

        int arraySize = pathPointArray.Num();
        if (arraySize == 0)
        {
            return;
        }

        if (arraySize == 1)
        {
           
            _enemy->GetBlackboardComponent()->SetValueAsObject(FName(TEXT("WaypointActor")), pathPointArray[0]);
            _enemy->GetBlackboardComponent()->SetValueAsVector(FName(TEXT("WaypointPosition")), pathPointArray[0]->GetActorLocation());
            return;
        }        

        

        int x = _enemy->TDGetRandomSpawnNunber() % arraySize;

        _enemy->GetBlackboardComponent()->SetValueAsObject(FName(TEXT("WaypointActor")), pathPointArray[x]);
        _enemy->GetBlackboardComponent()->SetValueAsVector(FName(TEXT("WaypointPosition")), pathPointArray[x]->GetActorLocation());

    }
}