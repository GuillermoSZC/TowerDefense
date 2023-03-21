#pragma once


#define GET_GAMEPLAY_TAG(TAG_NAME) \
	FGameplayTag::RequestGameplayTag(FName(TEXT(TAG_NAME)))


#define DEATH_TRIGGER_TAG "ability.trigger.death"
#define ABILITY1_TRIGGER_TAG "ability.trigger.ability1"