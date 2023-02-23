// Fill out your copyright notice in the Description page of Project Settings.


#include "IA/Task/TDCallWaypointFunctionTaskAI.h"

EBTNodeResult::Type UTDCallWaypointFunctionTaskAI::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);
    throw std::logic_error("The method or operation is not implemented.");
}

FString UTDCallWaypointFunctionTaskAI::GetStaticDescription() const
{
    Super::GetStaticDescription();
    throw std::logic_error("The method or operation is not implemented.");
}
