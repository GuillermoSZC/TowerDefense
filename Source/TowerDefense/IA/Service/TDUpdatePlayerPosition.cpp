// Fill out your copyright notice in the Description page of Project Settings.


#include "IA/Service/TDUpdatePlayerPosition.h"

UTDUpdatePlayerPosition::UTDUpdatePlayerPosition()
{
    PosKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UTDUpdatePlayerPosition,PosKey));
}

void UTDUpdatePlayerPosition::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    ATDEnemyController* enemyController = Cast<ATDEnemyController>(OwnerComp.GetOwner());
    ATDEnemy* enemy = enemyController->GetPawn<ATDEnemy>();
    UBlackboardComponent* blackboard = OwnerComp.GetBlackboardComponent();

    if (blackboard)
    {
        blackboard->SetValueAsVector(PosKey.SelectedKeyName, UTDGameData::TDGetPlayerRef()->GetActorLocation());

    }
}
