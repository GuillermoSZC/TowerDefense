// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "TDUpdateEnemyPosition.generated.h"

/**
 *
 */
UCLASS()
class TOWERDEFENSE_API UTDUpdateEnemyPosition : public UBTService
{
    GENERATED_BODY()

public:

    UTDUpdateEnemyPosition();

public:

    UPROPERTY(EditAnywhere, Category=Blackboard)
	FBlackboardKeySelector PosKey;

protected:


    void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:


public:

protected:

private:
};
