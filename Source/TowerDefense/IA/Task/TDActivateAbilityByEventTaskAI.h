// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "TDActivateAbilityByEventTaskAI.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UTDActivateAbilityByEventTaskAI : public UBTTaskNode
{
	GENERATED_BODY()
	

public:

	UPROPERTY(EditAnywhere)
	FGameplayTag eventTag;

protected:

private:

public:

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;



	FString GetStaticDescription() const override;


protected:

private:





};
