// Fill out your copyright notice in the Description page of Project Settings.


#include "IA/Service/TDUpdateEnemyPosition.h"

UTDUpdateEnemyPosition::UTDUpdateEnemyPosition()
{
    PosKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UTDUpdateEnemyPosition,PosKey));
}

void UTDUpdateEnemyPosition::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    ATDEnemyController* enemyController = Cast<ATDEnemyController>(OwnerComp.GetOwner());
    ATDEnemy* enemy = enemyController->GetPawn<ATDEnemy>();
    UBlackboardComponent* blackboard = OwnerComp.GetBlackboardComponent();

    if (blackboard)
    {
        blackboard->SetValueAsVector(PosKey.SelectedKeyName, enemy->GetActorLocation());

    }
}
