// Fill out your copyright notice in the Description page of Project Settings.


#include "AttributesSets/TDDamageAttributeSet.h"
#include "TDLevelAttributeSet.h"

void UTDDamageAttributeSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
    Super::PreAttributeBaseChange(Attribute, NewValue);
}

void UTDDamageAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
    Super::PreAttributeChange(Attribute, NewValue);
}

void UTDDamageAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
    Super::PostAttributeChange(Attribute, OldValue, NewValue);

    UAbilitySystemComponent* ASC = GetOwningAbilitySystemComponent();
    check(ASC);
    float newAttackSpeed = 0;



    if (Attribute == GetBaseAttackSpeedAttribute())
    {
        float percentage = ASC->GetNumericAttribute(GetPercentageAttackSpeedAttribute());
        newAttackSpeed = TDGetFinalAttackSpeed(NewValue, percentage);
        ASC->ApplyModToAttribute(GetattackSpeedAttribute(), EGameplayModOp::Type::Override, newAttackSpeed);

    }

    if (Attribute == GetPercentageAttackSpeedAttribute())
    {
        float BaseRate = ASC->GetNumericAttribute(GetBaseAttackSpeedAttribute());
        newAttackSpeed = TDGetFinalAttackSpeed(BaseRate, NewValue);
        ASC->ApplyModToAttribute(GetattackSpeedAttribute(), EGameplayModOp::Type::Override, newAttackSpeed);

    }


}

float UTDDamageAttributeSet::TDGetFinalAttackSpeed(float _baseRate, float _percentage)
{
    UAbilitySystemComponent* ASC = GetOwningAbilitySystemComponent();
    check(ASC);

    if (ASC->HasAttributeSetForAttribute(UTDLevelAttributeSet::GetlevelAttribute()))
    {
        float level = ASC->GetNumericAttribute(UTDLevelAttributeSet::GetlevelAttribute());
        return (_baseRate / (1 + (0.1f * (level-1)) + (_percentage / 100.f)));
    }
    else
    {
        return (_baseRate / (1 + (_percentage / 100.f)));
    }
}
