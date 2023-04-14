// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributesSets/TDAttributeSet.h"
#include "TDLevelAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UTDLevelAttributeSet : public UTDAttributeSet
{
	GENERATED_BODY()
			public:


public:


    UPROPERTY(Category = "Ability System | Attributes", VisibleAnywhere, BlueprintReadOnly)
        FGameplayAttributeData level;


protected:


private:


public:

    ATTRIBUTE_ACCESSORS(UTDLevelAttributeSet, level)


protected:

private:

};
