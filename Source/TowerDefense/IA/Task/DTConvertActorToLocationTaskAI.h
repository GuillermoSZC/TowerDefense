// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "DTConvertActorToLocationTaskAI.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UDTConvertActorToLocationTaskAI : public UBTTaskNode
{
	GENERATED_BODY()
public:

public:

protected:

private:




    FString GetStaticDescription() const override;

public:
    EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
    void OnGameplayTaskActivated(UGameplayTask& Task) override;

protected:


private:
};
