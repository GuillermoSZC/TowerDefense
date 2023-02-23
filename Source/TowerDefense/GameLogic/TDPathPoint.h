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
    UPROPERTY(Transient)
        TArray<ATDPathPoint*> pathPointArray;

    UPROPERTY()
        bool isBase;

protected:


private:


public:
    UFUNCTION()
        void TDArrivedAction(ATDEnemy* _enemy);

protected:


private:


};
