// Fill out your copyright notice in the Description page of Project Settings.

#include "TDTower.h"
#include "GameplayEffectTypes.h"
#include "GameLogic/TDGameData.h"
#include "Character/TDEnemy.h"
#include "GameLogic/TDRoundManager.h"
#include "AttributesSets/TDDamageAttributeSet.h"



//Sets default values
ATDTower::ATDTower()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//TowerAttributes = CreateDefaultSubobject<UTDTowerAttributeSet>(TEXT("Attributes"));

	timer = 0.f;


	abilitySystem = CreateDefaultSubobject<UAbilitySystemComponent>("AbilityComponent");
	elementComponent = CreateDefaultSubobject<UTDElementComponent>("ElementComponent");

}

bool ATDTower::TDIsDebugActive_Implementation() const
{
	return false;
}

UTDElementComponent* ATDTower::TDGetElementComponent_Implementation()
{
	return elementComponent;
}

void ATDTower::TDResetAttackTimer_Implementation()
{
	timer = periodAttack;
}

// Called when the game starts or when spawned
void ATDTower::BeginPlay()
{
	Super::BeginPlay();

	TDInitialize();
	
	UTDGameData::TDGetRoundManager()->FOnBuyPhaseStartDelegate.AddDynamic(this, &ATDTower::TDUpdateRoundValues);

}

void ATDTower::TDInitialize()
{

	const UAttributeSet* attributesInit = abilitySystem->InitStats(UTDDamageAttributeSet::StaticClass(), damageDatatable);
	TowerAttributes = Cast<UTDDamageAttributeSet>(attributesInit);
	periodAttack = TowerAttributes->GetattackSpeed();

    for (size_t i = 0; i < abiliyList.Num(); ++i)
    {
        FGameplayAbilitySpecHandle specHandle = abilitySystem->GiveAbility(FGameplayAbilitySpec(abiliyList[i].GetDefaultObject(), 1, 0));
    }

	TDActivateDelegates();


	if (periodAttack == 0.f)
	{
		ITDInterface::Execute_TGGApplyEffect(this);
		SetActorTickEnabled(false);
	}


	timer = 0.f;

}


UAbilitySystemComponent* ATDTower::GetAbilitySystemComponent() const
{
	return abilitySystem;
}

// Called every frame
void ATDTower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	timer += DeltaTime;

    //GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::SanitizeFloat(timer));

	if (timer >= periodAttack)
	{
		timer -= periodAttack;

		ITDInterface::Execute_TGGApplyEffect(this);

	}


}

ATDEnemy* ATDTower::TDGetEnemyInRange()
{

	TArray<ATDEnemy*> enemiesArray = UTDGameData::TDGetEnemiesArray();

	FVector ownerLocation = GetActorLocation();
	float TowerRadius = TowerAttributes->GetattackRange();
	ATDEnemy* minorDistanceToBase = nullptr;


	for (ATDEnemy* enemyIT : enemiesArray)
	{

		float distancetoEnemy = FVector::DistSquared(ownerLocation, enemyIT->GetActorLocation());

		if (distancetoEnemy <= TowerRadius)
		{
			if (minorDistanceToBase)
			{
				if (enemyIT->TDGetPathDistance() < minorDistanceToBase->TDGetPathDistance())
				{
					minorDistanceToBase = enemyIT;
				}
			}
			else
			{
				minorDistanceToBase = enemyIT;
			}

		}

	}

	return minorDistanceToBase;
}

void ATDTower::TDUpdateRoundValues(int32 _Round)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("UpdateTower"));

}


int ATDTower::TGGApplyEffect_Implementation()
{


	 //GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Funca"));

	return 0;
}





 void ATDTower::TDActivateDelegates()
 {
	 TowerDamageChangedDelegateHandle = abilitySystem->GetGameplayAttributeValueChangeDelegate(TowerAttributes->GetattackDamageAttribute()).AddUObject(this, &ATDTower::TDDamageChanged);
	 TowerRangeChangedDelegateHandle = abilitySystem->GetGameplayAttributeValueChangeDelegate(TowerAttributes->GetattackRangeAttribute()).AddUObject(this, &ATDTower::TDRangeChanged);
	 TowerPeriodAttackChangedDelegateHandle = abilitySystem->GetGameplayAttributeValueChangeDelegate(TowerAttributes->GetattackSpeedAttribute()).AddUObject(this, &ATDTower::TDPeriodAttackChanged);
 }



 void ATDTower::TDDamageChanged(const FOnAttributeChangeData& Data)
 {

 }

 void ATDTower::TDRangeChanged(const FOnAttributeChangeData& Data)
 {
	 FOnAttackRangeChangeDelegate.Broadcast(Data.NewValue);

 }

 void ATDTower::TDPeriodAttackChanged(const FOnAttributeChangeData& Data)
 {
	 periodAttack = Data.NewValue;
 }
