// Fill out your copyright notice in the Description page of Project Settings.

#include "TDTower.h"
#include "GameplayEffectTypes.h"
#include "GameLogic/TDGameData.h"
#include "Character/TDEnemy.h"
#include "GameLogic/TDRoundManager.h"
#include "AttributesSets/TDDamageAttributeSet.h"
#include "GameLogic/TDElementComponent.h"
#include "UI/TDTowerUpgrade.h"
#include "Character/TDPlayerCharacter.h"


UTDTowerUpgrade* ATDTower::uiUpgradeRef = nullptr;


//Sets default values
ATDTower::ATDTower()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//TowerAttributes = CreateDefaultSubobject<UTDTowerAttributeSet>(TEXT("Attributes"));

	timer = 0.f;

	isUIActive = false;

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
	OnClicked.AddDynamic(this, &ATDTower::TDOnClickedTower);

	if (elementComponent)
	{
		elementComponent->OnElementChangeDelegate.AddUniqueDynamic(this, &ATDTower::TDOnElementChange);
	}

	distSquared = distanceToUI * distanceToUI;

	if (uiUpgradeClass && !uiUpgradeRef)
	{
		uiUpgradeRef = CreateWidget<UTDTowerUpgrade>(GetWorld(), uiUpgradeClass);
		uiUpgradeRef->AddToViewport();
		uiUpgradeRef->SetVisibility(ESlateVisibility::Collapsed);
	}
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

	if (isUIActive && !TDCheckPlayerInRange())
	{
		TDHideUI();
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


void ATDTower::TDOnElementChange_Implementation(EElements _newElement)
{

}

void ATDTower::TDHideUI_Implementation()
{
	isUIActive = false;

	if (uiUpgradeRef)
	{
		uiUpgradeRef->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void ATDTower::TDVisibleUI_Implementation()
{
	isUIActive = true;

	if (uiUpgradeRef)
	{
		uiUpgradeRef->SetVisibility(ESlateVisibility::Visible);
	}
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

 float ATDTower::TDCheckDistanceWithPlayer()
 {
	 float distanceSquared;

	 FVector ownerLocation = GetActorLocation();
	 FVector playerLocation = UTDGameData::TDGetPlayerRef()->GetActorLocation();
	 distanceSquared = FVector::DistSquared2D(ownerLocation, playerLocation);

	 return distanceSquared;
 }

 bool ATDTower::TDCheckPlayerInRange()
 {
	 if (TDCheckDistanceWithPlayer() > distSquared)
	 {
		 return false;
	 }

	 return true;
 }

 bool ATDTower::TDCanShowUI()
 {
	 if (!TDCheckPlayerInRange())
	 {
		 return false;
	 }

	 if (UTDGameData::TDGetRoundManager()->TDGetActualPhase() != GamePhase::BuyPhase)
	 {
		 return false;
	 }

	 return true;
 }
