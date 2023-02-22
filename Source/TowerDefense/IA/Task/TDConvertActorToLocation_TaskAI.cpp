

#include "IA/Task/TDConvertActorToLocation_TaskAI.h"


EBTNodeResult::Type UTDConvertActorToLocation_TaskAI::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

//     resetblackboardvaluetask HowlOfIron
// 
//     blackboard->GetValueAsObject()
//     blackboard->GetValueAsVector()

//HIEnemyTask_AddNumberToKey.cpp constructor
// addKey.AddObjectFilter


    return EBTNodeResult::Succeeded;
}

void UTDConvertActorToLocation_TaskAI::OnGameplayTaskActivated(UGameplayTask& Task)
{
   
}

FString UTDConvertActorToLocation_TaskAI::GetStaticDescription() const
{
    return FString(TEXT("Coso"));
}