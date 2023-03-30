// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributesSets/TDAttributeSet.h"
#include "TDHealthAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UTDHealthAttributeSet : public UTDAttributeSet
{
	GENERATED_BODY()
	

		public:


public:


    UPROPERTY(Category = "Ability System | Attributes", VisibleAnywhere, BlueprintReadOnly)
        FGameplayAttributeData maxHealth;

    UPROPERTY(Category = "Ability System | Attributes", VisibleAnywhere, BlueprintReadOnly)
        FGameplayAttributeData health;

protected:


private:


public:

    ATTRIBUTE_ACCESSORS(UTDHealthAttributeSet, maxHealth)
        ATTRIBUTE_ACCESSORS(UTDHealthAttributeSet, health)



protected:


    virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
    virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
    virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;


    void ClampAttribute(const FGameplayAttribute& Attribute, float& NewValue) const;

private:


};
