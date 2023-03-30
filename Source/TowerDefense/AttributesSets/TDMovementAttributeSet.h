// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameLogic/TDAttributeSet.h"
#include "TDMovementAttributeSet.generated.h"

/**
 *
 */
UCLASS()
class TOWERDEFENSE_API UTDMovementAttributeSet : public UTDAttributeSet
{
    GENERATED_BODY()


public:


public:


    UPROPERTY(Category = "Ability System | Attributes", VisibleAnywhere, BlueprintReadOnly)
        FGameplayAttributeData movementSpeed;

  
protected:


private:


public:

    ATTRIBUTE_ACCESSORS(UTDMovementAttributeSet, movementSpeed)



protected:


private:



};
