#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "TDConvertActorToLocation_TaskAI.generated.h"

/**
 *
 */
UCLASS()
class TOWERDEFENSE_API UTDConvertActorToLocation_TaskAI : public UBTTaskNode
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
