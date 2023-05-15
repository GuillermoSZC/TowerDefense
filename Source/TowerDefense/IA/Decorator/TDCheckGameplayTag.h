// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include <AbilitySystemComponent.h>
#include "TDCheckGameplayTag.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UTDDecoratorCheckGameplayTag : public UBTDecorator
{
	GENERATED_BODY()
	


public:
	UTDDecoratorCheckGameplayTag();
	~UTDDecoratorCheckGameplayTag() {};


	UPROPERTY(EditAnywhere, Category = GameplayTagCheck)
	bool inverseCondition;


private:
	UPROPERTY(EditAnywhere, Category = GameplayTagCheck)
		EGameplayContainerMatchType matchType;

	UPROPERTY(EditAnywhere, Category = GameplayTagCheck)
		FGameplayTagContainer gameplayTags;

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	virtual void OnNodeActivation(FBehaviorTreeSearchData& SearchData) override;
	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);

private:
	bool CheckHasAllGameplayTags(UAbilitySystemComponent* ownerAbilitySystem) const;
	bool CheckHasAnyGameplayTags(UAbilitySystemComponent* ownerAbilitySystem) const;












};
