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

    float refreshPathTime;
    float tickCounterTime;
    float pathDsitance;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;


    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
        float TDCalculatePathDistance();

    UFUNCTION(BlueprintCallable)
        float TDGetPathDistance();


protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

private:




};
