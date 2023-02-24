#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "TDPathPoint.generated.h"

class ATDEnemy;

UCLASS()
class TOWERDEFENSE_API ATDPathPoint : public ATargetPoint
{
    GENERATED_BODY()
public:
    ATDPathPoint();

public:
    UPROPERTY(EditAnywhere, Category = "PathFollow")
        TArray<ATDPathPoint*> pathPointArray;

    UPROPERTY(EditAnywhere, Category = "PathFollow")
        bool isBase;

protected:


private:


public:
    UFUNCTION()
        void TDArrivedAction(ATDEnemyController* _enemy);

protected:


private:


};
