#pragma once

#include "CoreMinimal.h"
#include "Character/TDPlayerCharacter.h"
#include "TDEnemy.generated.h"

UCLASS()
class TOWERDEFENSE_API ATDEnemy : public ATDPlayerCharacter
{
    GENERATED_BODY()
public:
    ATDEnemy();

protected:


public:


private:


public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

private:


};
