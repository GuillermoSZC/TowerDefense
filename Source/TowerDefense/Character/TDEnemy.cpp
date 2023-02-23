#include "Character/TDEnemy.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GameLogic/TDGameData.h"
#include "TDEnemyAttributeSet.h"

#include "TDMacros.h"
#include "GameplayEffectTypes.h"
#include "GameplayTagsManager.h"


ATDEnemy::ATDEnemy()
{
    PrimaryActorTick.bCanEverTick = true;

	refreshPathTime = 0.2f;
	tickCounterTime = 0.f;

}

void ATDEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (tickCounterTime >= refreshPathTime)
	{
		pathDsitance = TDCalculatePathDistance();

		tickCounterTime -= refreshPathTime;

	}

	tickCounterTime += DeltaTime;

}

float ATDEnemy::TDGetPathDistance()
{
	return  pathDsitance;
}

void ATDEnemy::BeginPlay()
{
	Super::BeginPlay();

	TDInitialize();

}

void ATDEnemy::TDInitialize()
{

    UTDGameData::TDAddEnmemyToArray(this);


    const UAttributeSet* attributesInit = abilitySystem->InitStats(UTDEnemyAttributeSet::StaticClass(), statsDatatable);
	EnemyAttributes = Cast<UTDEnemyAttributeSet>(attributesInit);

    for (size_t i = 0; i < abiliyList.Num(); ++i)
    {
        FGameplayAbilitySpecHandle specHandle = abilitySystem->GiveAbility(FGameplayAbilitySpec(abiliyList[i].GetDefaultObject(), 1, 0));
    }


	TDActivateDelegates();
}

void ATDEnemy::TDActivateDelegates()
{

    abilitySystem->GetGameplayAttributeValueChangeDelegate(EnemyAttributes->GethealthAttribute()).AddUObject(this, &ATDEnemy::TDHealthChanged);
    abilitySystem->GetGameplayAttributeValueChangeDelegate(EnemyAttributes->GetmaxHealthAttribute()).AddUObject(this, &ATDEnemy::TDmaxHealthChanged);
	abilitySystem->GetGameplayAttributeValueChangeDelegate(EnemyAttributes->GetattackDamageAttribute()).AddUObject(this, &ATDEnemy::TDAttackDamageChanged);
	abilitySystem->GetGameplayAttributeValueChangeDelegate(EnemyAttributes->GetattackRangeAttribute()).AddUObject(this, &ATDEnemy::TDAttackRangeChanged);
	abilitySystem->GetGameplayAttributeValueChangeDelegate(EnemyAttributes->GetattackSpeedAttribute()).AddUObject(this, &ATDEnemy::TDAttackSpeedChanged);
	abilitySystem->GetGameplayAttributeValueChangeDelegate(EnemyAttributes->GetmovementSpeedAttribute()).AddUObject(this, &ATDEnemy::TDMovementSpeedChanged);


}

void ATDEnemy::TDmaxHealthChanged(const FOnAttributeChangeData& Data)
{

}

void ATDEnemy::TDHealthChanged(const FOnAttributeChangeData& Data)
{
	if (Data.NewValue <= 0.f)
    {
        FGameplayEventData DataEvent;
		//FGameplayTag tagjump = FGameplayTag::RequestGameplayTag(FName(TEXT("ability.trigger")));
		//FGameplayTag tagjump;
	
		//UGameplayTagsManager::Get().RequestGameplayTag(FName(TEXT("ability.trigger")));
		
		

		//UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this, FGameplayTag::RequestGameplayTag(FName(TEXT("Ability.Trigger.Death"))) , DataEvent);

	}
}

void ATDEnemy::TDAttackDamageChanged(const FOnAttributeChangeData& Data)
{

}

void ATDEnemy::TDAttackRangeChanged(const FOnAttributeChangeData& Data)
{

}

void ATDEnemy::TDAttackSpeedChanged(const FOnAttributeChangeData& Data)
{

}

void ATDEnemy::TDMovementSpeedChanged(const FOnAttributeChangeData& Data)
{

}

