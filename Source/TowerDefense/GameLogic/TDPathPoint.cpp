#include "GameLogic/TDPathPoint.h"
#include "Character/TDEnemyController.h"
#include "Character/TDEnemy.h"
#include "AIModule/Classes/BehaviorTree/BlackboardComponent.h"

ATDPathPoint::ATDPathPoint()
{
    
}

void ATDPathPoint::TDArrivedAction(ATDEnemy* _enemy)
{
    if (!isBase)
    {
        if (pathPointArray.Num() == 1)
        {
            ATDEnemyController* enemyController = Cast<ATDEnemyController>(_enemy->GetController());
            enemyController->GetBlackboardComponent()->SetValueAsObject(FName(TEXT("WaypointActor")), this);
            enemyController->GetBlackboardComponent()->SetValueAsVector(FName(TEXT("WaypointPosition")), GetActorLocation());
        }        
    }
}