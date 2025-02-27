// Fill out your copyright notice in the Description page of Project Settings.


#include "IA/Decorator/TDCheckDistance.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include <AIModule/Classes/BehaviorTree/Blackboard/BlackboardKeyType.h>
#include <AIModule/Classes/BehaviorTree/BlackboardComponent.h>
#include "Character/TDEnemyController.h"
#include "Character/TDEnemy.h"

UTDCheckDistance::UTDCheckDistance()
{
    BlackboardKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UTDCheckDistance, BlackboardKey));
    BlackboardKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UTDCheckDistance, BlackboardKey), AActor::StaticClass());
}

bool UTDCheckDistance::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
    Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

    ATDEnemyController* enemyController = Cast<ATDEnemyController>(OwnerComp.GetOwner());
    ATDEnemy* enemy = enemyController->GetPawn<ATDEnemy>();
    UBlackboardComponent* blackboard = OwnerComp.GetBlackboardComponent();

    bool vfound;
    float fGreaterDistance = enemy->abilitySystem->GetGameplayAttributeValue(GreaterDistance,vfound);

    float shortDistanceSquared;
    float GreaterDistanceSquared;

    shortDistanceSquared = shortDistance * shortDistance;
    GreaterDistanceSquared = fGreaterDistance * fGreaterDistance;

   

    TSubclassOf<UBlackboardKeyType> tempkey = blackboard->GetKeyType(blackboard->GetKeyID(BlackboardKey.SelectedKeyName));

    FVector OwnerLocation = enemy->GetActorLocation();
    FVector locationToDistance;

    if (tempkey == UBlackboardKeyType_Object::StaticClass())
    {
        AActor* actorToDistance = Cast<AActor>(blackboard->GetValueAsObject(BlackboardKey.SelectedKeyName));
        locationToDistance = actorToDistance->GetActorLocation();
    }
    else if (tempkey == UBlackboardKeyType_Vector::StaticClass())
    {
        locationToDistance = blackboard->GetValueAsVector(BlackboardKey.SelectedKeyName);
    }
    else
    {
        return false;
    }


    double distance = FVector::DistSquared2D(OwnerLocation, locationToDistance);

    switch (DistanceType)
    {
        case TypeDistance::lessThan:
        {

            if (distance <= shortDistanceSquared)
            {
                return true;
            }

        }
        break;

        case TypeDistance::BetweenDistance:
        {

            if (distance >= shortDistanceSquared && distance <= GreaterDistanceSquared)
            {
                return true;
            }

        }
        break;

        case TypeDistance::GreaterThan:
        {
            if (distance >= GreaterDistanceSquared)
            {
                return true;
            }
        }
        break;

        default:
        {

        }

    }

    return false;

}

EBlackboardNotificationResult UTDCheckDistance::OnBlackboardKeyValueChange(const UBlackboardComponent& Blackboard, FBlackboard::FKey ChangedKeyID)
{

    UBehaviorTreeComponent* BehaviorComp = (UBehaviorTreeComponent*)Blackboard.GetBrainComponent();
    if (BehaviorComp == nullptr)
    {
        return EBlackboardNotificationResult::RemoveObserver;
    }


//     if (BlackboardKey.GetSelectedKeyID() == ChangedKeyID)
//     {
//         const EBTDecoratorAbortRequest RequestMode = EBTDecoratorAbortRequest::ConditionPassing;
//         ConditionalFlowAbort(*BehaviorComp, RequestMode);
//     }

    for (FBlackboardKeySelector iter : KeysToLook)
    {
        if (iter.GetSelectedKeyID() == ChangedKeyID)
        {
            const EBTDecoratorAbortRequest RequestMode = EBTDecoratorAbortRequest::ConditionPassing;
            ConditionalFlowAbort(*BehaviorComp, RequestMode);
        }
    }

    return EBlackboardNotificationResult::ContinueObserving;
}

FString UTDCheckDistance::GetStaticDescription() const
{

    return FString(TEXT("Check distance with the BB key"));
}
