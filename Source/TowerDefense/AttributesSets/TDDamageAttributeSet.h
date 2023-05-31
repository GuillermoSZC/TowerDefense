// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributesSets/TDAttributeSet.h"
#include "TDDamageAttributeSet.generated.h"

/**
 *
 */
UCLASS()
class TOWERDEFENSE_API UTDDamageAttributeSet : public UTDAttributeSet
{
    GENERATED_BODY()


public:


public:


    UPROPERTY(Category = "Ability System | Attributes", VisibleAnywhere, BlueprintReadOnly)
        FGameplayAttributeData attackDamage;

    UPROPERTY(Category = "Ability System | Attributes", VisibleAnywhere, BlueprintReadOnly)
        FGameplayAttributeData attackSpeed;

    UPROPERTY(Category = "Ability System | Attributes", VisibleAnywhere, BlueprintReadOnly)
        FGameplayAttributeData BaseAttackSpeed;

    UPROPERTY(Category = "Ability System | Attributes", VisibleAnywhere, BlueprintReadOnly)
        FGameplayAttributeData PercentageAttackSpeed;

    UPROPERTY(Category = "Ability System | Attributes", VisibleAnywhere, BlueprintReadOnly)
        FGameplayAttributeData attackRange;

protected:


private:


public:

    ATTRIBUTE_ACCESSORS(UTDDamageAttributeSet, attackDamage)
        ATTRIBUTE_ACCESSORS(UTDDamageAttributeSet, attackSpeed)
        ATTRIBUTE_ACCESSORS(UTDDamageAttributeSet, BaseAttackSpeed)
        ATTRIBUTE_ACCESSORS(UTDDamageAttributeSet, PercentageAttackSpeed)
        ATTRIBUTE_ACCESSORS(UTDDamageAttributeSet, attackRange)


protected:

    virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
    virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
    virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;

private:

    float TDGetFinalAttackSpeed(float _baseRate, float _percentage);

};
