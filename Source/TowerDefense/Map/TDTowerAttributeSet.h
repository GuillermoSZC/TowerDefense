// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "../GameLogic/TDAttributeSet.h"
#include "TDTowerAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UTDTowerAttributeSet : public UTDAttributeSet
{
	GENERATED_BODY()


public:

    UTDTowerAttributeSet();

public:

    UPROPERTY(Category = "Ability System | Attributes", VisibleAnywhere, BlueprintReadOnly)
        FGameplayAttributeData damage;

    UPROPERTY(Category = "Ability System | Attributes", VisibleAnywhere, BlueprintReadOnly)
        FGameplayAttributeData range;

    UPROPERTY(Category = "Ability System | Attributes", VisibleAnywhere, BlueprintReadOnly)
        FGameplayAttributeData attackSpeed;

protected:


private:


public:

        ATTRIBUTE_ACCESSORS(UTGTowerAttributeSet, damage)
        ATTRIBUTE_ACCESSORS(UTGTowerAttributeSet, range)
        ATTRIBUTE_ACCESSORS(UTGTowerAttributeSet, attackSpeed)


        //     virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
        //     virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
        //     void PostGameplayEffectExecute_SingleAttribute(const struct FGameplayEffectModCallbackData& Data, FName MemberName, FGameplayAttributeData& Attrib, FGameplayAttributeData& MaxAttrib);




protected:


private:
	
};
