// Fill out your copyright notice in the Description page of Project Settings.


#include "IA/Task/DTConvertActorToLocationTaskAI.h"

EBTNodeResult::Type UDTConvertActorToLocationTaskAI::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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

void UDTConvertActorToLocationTaskAI::OnGameplayTaskActivated(UGameplayTask& Task)
{

}

FString UDTConvertActorToLocationTaskAI::GetStaticDescription() const
{
    return FString(TEXT("Coso"));
}