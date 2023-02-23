// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "TDCallWaypointFunctionTaskAI.generated.h"

/**
 *
 */
UCLASS()
class TOWERDEFENSE_API UTDCallWaypointFunctionTaskAI : public UBTTaskNode
{
    GENERATED_BODY()
public:


public:


protected:


private:



    EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;


    FString GetStaticDescription() const override;

public:


protected:


private:


};
