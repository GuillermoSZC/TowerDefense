#include "IA/Task/TDCallWaypointFunctionTaskAI.h"
#include "AIModule/Classes/BehaviorTree/BlackboardComponent.h"
#include "GameLogic/TDPathPoint.h"
#include "Character/TDEnemyController.h"
#include "Character/TDEnemy.h"

EBTNodeResult::Type UTDCallWaypointFunctionTaskAI::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

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
            pathPoint->TDArrivedAction(enemyController);

            return EBTNodeResult::Succeeded;
        }
    }

    return EBTNodeResult::Failed;
}

FString UTDCallWaypointFunctionTaskAI::GetStaticDescription() const
{
    Super::GetStaticDescription();

    return FString(TEXT("CallArrivedWaypoint"));
}
