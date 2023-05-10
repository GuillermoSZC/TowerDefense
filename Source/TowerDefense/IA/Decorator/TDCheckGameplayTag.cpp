// Fill out your copyright notice in the Description page of Project Settings.


#include "IA/Decorator/TDCheckGameplayTag.h"
#include "GameplayTagAssetInterface.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "Character/TDCharacter.h"
#include <AIModule/Classes/AIController.h>

UTDDecoratorCheckGameplayTag::UTDDecoratorCheckGameplayTag()
{
    bNotifyActivation = true;
    bNotifyBecomeRelevant = true;
    bNotifyTick = true;
}

bool UTDDecoratorCheckGameplayTag::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
    const UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
    if (BlackboardComp == NULL)
    {
        return false;
    }

    AAIController* ownerController = Cast<AAIController>(OwnerComp.GetOwner());
    ATDCharacter* characterOwner = Cast<ATDCharacter>(ownerController->GetPawn());
    if (!characterOwner)
    {
        return false;
    }

    UAbilitySystemComponent* abilitySystem = characterOwner->abilitySystem;
 
    switch (matchType)
    {
    case EGameplayContainerMatchType::All:
        if (inverseCondition)
        {
            return !CheckHasAllGameplayTags(abilitySystem);
        }
        else
        {
            return CheckHasAllGameplayTags(abilitySystem);
        }
        break;

    case EGameplayContainerMatchType::Any:
        if (inverseCondition)
        {
            return !CheckHasAnyGameplayTags(abilitySystem);
        }
        else
        {
            return CheckHasAnyGameplayTags(abilitySystem);
        }
        break;

    default:
    {
        UE_LOG(LogBehaviorTree, Warning, TEXT("Invalid value for TagsToMatch (EGameplayContainerMatchType) %d.  Should only be Any or All."), static_cast<int32>(matchType));
        return false;
    }
    }
}

void UTDDecoratorCheckGameplayTag::OnNodeActivation(FBehaviorTreeSearchData& SearchData)
{
    Super::OnNodeActivation(SearchData);
}

void UTDDecoratorCheckGameplayTag::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::OnBecomeRelevant(OwnerComp, NodeMemory);

    OwnerComp.RequestExecution(this);
}

void UTDDecoratorCheckGameplayTag::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    OwnerComp.RequestExecution(this);
}

bool UTDDecoratorCheckGameplayTag::CheckHasAllGameplayTags(UAbilitySystemComponent* ownerAbilitySystem) const
{
    FGameplayTagContainer OwnedTags;
    ownerAbilitySystem->GetOwnedGameplayTags(OwnedTags);

    return OwnedTags.HasAll(gameplayTags);
}

bool UTDDecoratorCheckGameplayTag::CheckHasAnyGameplayTags(UAbilitySystemComponent* ownerAbilitySystem) const
{
    FGameplayTagContainer OwnedTags;
    ownerAbilitySystem->GetOwnedGameplayTags(OwnedTags);

    return OwnedTags.HasAny(gameplayTags);
}