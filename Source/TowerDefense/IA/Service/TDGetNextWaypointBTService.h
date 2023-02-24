// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "TDGetNextWaypointBTService.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UTDGetNextWaypointBTService : public UBTService
{
	GENERATED_BODY()
	
public:

	UTDGetNextWaypointBTService();

public:
	UPROPERTY(EditAnywhere)
	float ArriveDistance;

protected:



	void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:


public:


protected:


private:

};
