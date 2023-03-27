#pragma once


#define GET_GAMEPLAY_TAG(TAG_NAME) \
	FGameplayTag::RequestGameplayTag(FName(TEXT(TAG_NAME)))


#define DEATH_TRIGGER_TAG "ability.trigger.death"
#define ABILITY1_TRIGGER_TAG "ability.trigger.ability1"
#define ENEMYHIT_TRIGGER_TAG "ability.trigger.enemyHit"



#define TDDECLARE_ATTRIBUTE_CAPTUREDEF(P,T) \
	FProperty* P##T##Property; \
	FGameplayEffectAttributeCaptureDefinition P##T##Def; \

#define TDDEFINE_ATTRIBUTE_CAPTUREDEF(S, P, T, B) \
{ \
	P##T##Property = FindFieldChecked<FProperty>(S::StaticClass(), GET_MEMBER_NAME_CHECKED(S, P)); \
	P##T##Def = FGameplayEffectAttributeCaptureDefinition(P##T##Property, EGameplayEffectAttributeCaptureSource::T, B); \
}


