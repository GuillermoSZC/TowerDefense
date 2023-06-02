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
#include <UMG/Public/Blueprint/WidgetBlueprintLibrary.h>
#include "Character/TDPlayerController.h"
#include "AttributesSets/TDLevelAttributeSet.h"
#include "GameLogic/TDCostManager.h"



//Sets default values
ATDTower::ATDTower()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    timer = 0.f;


    abilitySystem = CreateDefaultSubobject<UAbilitySystemComponent>("AbilityComponent");
    elementComponent = CreateDefaultSubobject<UTDElementComponent>("ElementComponent");

}



FGameplayTag ATDTower::TDGetTagClass_Implementation()
{
    return TagClass;
}

//Blueprints cost
void ATDTower::TDCalcultateCostWithLoot_Implementation(FBuyCost& _cost, ELootItems _item /*= ELootItems::None*/)
{
    bool found = false;
    float level = abilitySystem->GetGameplayAttributeValue(UTDLevelAttributeSet::GetlevelAttribute(), found);
    _cost.BPItem = BPToUprgade;
    ensure(found);
    UTDGameData::TDGetCostManager()->TDCalculateUpgradeCost(_cost, level);
}


bool ATDTower::TDCanAffordCostWithLoot_Implementation(FBuyCost& _cost)
{
    return UTDGameData::TDGetCostManager()->TDCanAffordBuy(_cost);
}

bool ATDTower::TDCommitBuyUpgrade_Implementation(ELootItems _item)
{
    FBuyCost cost = FBuyCost();

    if (_item == ELootItems::None)
    {
        cost.BPItem = BPToUprgade;
        ITDCostInterface::Execute_TDCalcultateCostWithLoot(this, cost, cost.BPItem);

        if (!ITDCostInterface::Execute_TDCanAffordCostWithLoot(this, cost))
        {
            return false;
        }

        UTDGameData::TDGetCostManager()->TDCommitResources(cost);
        return true;
    }


    if (_item == ELootItems::Fire || _item == ELootItems::Ice || _item == ELootItems::Plasma)
    {

        ITDCostInterface::Execute_TDCalculateElementChangeCost(this, cost, _item);
        if (!ITDCostInterface::Execute_TDCanAffordCostWithLoot(this, cost))
        {
            return false;
        }

        UTDGameData::TDGetCostManager()->TDCommitResources(cost); 
        return true;

    }




    return false;

}



//Gem Cost

void ATDTower::TDCalculateElementChangeCost_Implementation(FBuyCost& _cost, ELootItems _itemElement)
{

    EElements spawnedElement = elementComponent->TDGetSpawnedElement();
    EElements elementToSwitch = EElements::None;
    _cost.GemItem = _itemElement;

    switch (_itemElement)
    {
    case ELootItems::Fire:
    {

        elementToSwitch = EElements::Fire;
    }
    break;

    case ELootItems::Ice:
    {
        elementToSwitch = EElements::Freeze;
    }
    break;

    case ELootItems::Plasma:
    {
        elementToSwitch = EElements::Plasma;
    }
    break;

    default:
    {
    }
    break;
    }

    UTDGameData::TDGetCostManager()->TDCalculateElementChange(_cost, elementToSwitch, spawnedElement);
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

    if (elementComponent)
    {

        elementComponent->OnElementChangeDelegate.AddUniqueDynamic(this, &ATDTower::TDOnElementChange);

    }
    UTDGameData::TDGetCostManager()->TDTowerSpawn(this);
}

void ATDTower::TDInitialize()
{

    const UAttributeSet* attributesInit = abilitySystem->InitStats(UTDDamageAttributeSet::StaticClass(), damageDatatable);
    TowerAttributes = Cast<UTDDamageAttributeSet>(attributesInit);
    periodAttack = TowerAttributes->GetattackSpeed();
    //abilitySystem->ApplyModToAttribute(TowerAttributes->GetattackSpeedAttribute(), EGameplayModOp::Type::Override, TowerAttributes->GetBaseAttackSpeed());

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

ELootItems ATDTower::TDGetItemToUpgrade()
{
    return BPToUprgade;
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


void ATDTower::TDOnElementChange_Implementation(EElements _newElement)
{

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
    TowerBaseAttackSpeedChangedDelegateHandle = abilitySystem->GetGameplayAttributeValueChangeDelegate(TowerAttributes->GetBaseAttackSpeedAttribute()).AddUObject(this, &ATDTower::TDPercentageSpeedChanged);
    TowerPercentageAttackSpeedChangedDelegateHandle = abilitySystem->GetGameplayAttributeValueChangeDelegate(TowerAttributes->GetPercentageAttackSpeedAttribute()).AddUObject(this, &ATDTower::TDBaseAttackSpeedChanged);
    LevelUpChangedDelegateHandle = abilitySystem->GetGameplayAttributeValueChangeDelegate(UTDLevelAttributeSet::GetlevelAttribute()).AddUObject(this, &ATDTower::TDLevelUpChanged);
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
    
    periodAttack = abilitySystem->GetNumericAttribute(TowerAttributes->GetattackSpeedAttribute());

}

void ATDTower::TDLevelUpChanged(const FOnAttributeChangeData& Data)
{
    
    if (((int)Data.NewValue - 1) % UpgradeEveryXLevel == 0)
    {
        UGameplayEffect* effectRef = Cast<UGameplayEffect>(levelUpgrade->GetDefaultObject());
        FGameplayEffectContextHandle context;
        abilitySystem->ApplyGameplayEffectToSelf(effectRef, 0, context);
        effectRef->ConditionalBeginDestroy();
    }
    FOnLevelUpChangeDelegate.Broadcast(Data.NewValue);
}

void ATDTower::TDPercentageSpeedChanged(const FOnAttributeChangeData& Data)
{

}

void ATDTower::TDBaseAttackSpeedChanged(const FOnAttributeChangeData& Data)
{

}

