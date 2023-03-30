// Fill out your copyright notice in the Description page of Project Settings.


#include "IA/Task/TDActivateAbilityByEventTaskAI.h"
#include "TDMacros.h"
#include "AbilitySystemBlueprintLibrary.h"

EBTNodeResult::Type UTDActivateAbilityByEventTaskAI::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    ATDEnemyController* enemyController = Cast<ATDEnemyController>(OwnerComp.GetOwner());
    ATDEnemy* enemy = enemyController->GetPawn<ATDEnemy>();
    UBlackboardComponent* blackboard = OwnerComp.GetBlackboardComponent();

    FGameplayEventData payloadData;
     
    UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(enemy, eventTag, payloadData);


    return EBTNodeResult::Succeeded;

}


FString UTDActivateAbilityByEventTaskAI::GetStaticDescription() const
{
    Super::GetStaticDescription();

    return FString(TEXT("Send Gameplay Event To Enemy Actor"));
}
