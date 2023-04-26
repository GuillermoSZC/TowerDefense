// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "TDCheckDistance.generated.h"


UENUM()
enum TypeDistance
{
	lessThan,
	BetweenDistance,
	GreaterThan
};

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UTDCheckDistance : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()
	

public:

	UTDCheckDistance();

public:



	UPROPERTY(EditAnywhere)
	TEnumAsByte<TypeDistance> DistanceType;

	UPROPERTY(EditAnywhere)
	float shortDistance;

	UPROPERTY(EditAnywhere)
	float GreaterDistance;

	UPROPERTY(EditAnywhere)
	TArray<FBlackboardKeySelector> KeysToLook;

protected:



private:



public:

protected:

	bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;


private:


	virtual EBlackboardNotificationResult OnBlackboardKeyValueChange(const UBlackboardComponent& Blackboard, FBlackboard::FKey ChangedKeyID) override;
	virtual FString GetStaticDescription() const override;


};
