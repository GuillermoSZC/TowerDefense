#include "Character/TDEnemy.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GameLogic/TDGameData.h"
#include "GameplayTagContainer.h"
#include "TDMacros.h"
#include "GameLogic/TDPathPoint.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Map/TDBase.h"
#include "Components/CapsuleComponent.h"
#include "TDEnemyController.h"
#include "AIModule/Classes/BrainComponent.h"
#include "GameLogic/TDObjectPooler.h"
#include "Components/WidgetComponent.h"
#include "UI/Utilities/TDHealthBar.h"
#include "AttributesSets/TDHealthAttributeSet.h"
#include "AttributesSets/TDDamageAttributeSet.h"
#include "AttributesSets/TDMovementAttributeSet.h"
#include "AIModule/Classes/BehaviorTree/BlackboardComponent.h"


ATDEnemy::ATDEnemy()
{
    PrimaryActorTick.bCanEverTick = true;

    refreshPathTime = 0.08f;
    tickCounterTime = 0.f;

    widgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
    widgetComponent->SetupAttachment(RootComponent);


    skeletalWeaponComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalWeaponMesh"));
    skeletalWeaponComponent->SetupAttachment(GetMesh());

    StaticWeaponComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaicWeaponMesh"));
    StaticWeaponComponent->SetupAttachment(GetMesh());
}



void ATDEnemy::TDCharacterDeath_Implementation()
{
    UTDGameData::TDGetObjectPooler()->TDAddEnemyToPool(this);
    TDSetDisable();

}

UAnimMontage* ATDEnemy::TDGetSketalMeshMontage_Implementation()
{
    return montageRef;
}

void ATDEnemy::TDHealthChanged(const FOnAttributeChangeData& Data)
{
    Super::TDHealthChanged(Data);

    if (Data.NewValue <= 0.f)
    {
        healthBar->SetVisibility(ESlateVisibility::Collapsed);
    }

}

void ATDEnemy::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if (isActive)
    {
        if (tickCounterTime >= refreshPathTime)
        {
            pathDsitance = TDCalculatePathDistance();
            tickCounterTime -= refreshPathTime;
        }
        tickCounterTime += DeltaTime;
    }
}

float ATDEnemy::TDCalculatePathDistance()
{
    float totalDistance = 0.f;

    if (PathPointsArray.Num() > 0)
    {
        for (int i = 0; i <= PathPointsArray.Num() - 1; ++i)
        {
            if (!PathPointsArray[i]->TDGetIsBase())
            {
                totalDistance += FVector::DistSquared2D(PathPointsArray[i]->GetActorLocation(), PathPointsArray[i + 1]->GetActorLocation());
            }
            else
            {
                totalDistance += FVector::DistSquared2D(PathPointsArray[i]->GetActorLocation(), UTDGameData::TDGetBaseActor()->GetActorLocation());
            }

        }

        totalDistance += FVector::DistSquared2D(PathPointsArray[0]->GetActorLocation(), GetActorLocation());
    }
    if (PathPointsArray.Num() == 0)
    {
        totalDistance += FVector::DistSquared2D(UTDGameData::TDGetBaseActor()->GetActorLocation(), GetActorLocation());
    }




    return totalDistance;

}

float ATDEnemy::TDGetPathDistance()
{
    return  pathDsitance;
}

void ATDEnemy::TDSetPath(ATDPathPoint* _pathPointRef)
{
    PathPointsArray.Empty();

    bool isBase = false;
    PathPointsArray.Add(_pathPointRef);
    isBase = _pathPointRef->TDGetIsBase();
    ATDPathPoint* actualref = _pathPointRef;

    while (!isBase)
    {
        actualref = actualref->TDGetNextPoint();
        PathPointsArray.Add(actualref);
        isBase = actualref->TDGetIsBase();
    }
}

ATDPathPoint* ATDEnemy::TDGetNextPathPoint()
{
    if (!PathPointsArray.IsEmpty())
    {
        PathPointsArray.RemoveAt(0);
        if (!PathPointsArray.IsEmpty())
        {
            return PathPointsArray[0];
        }
    }
    return nullptr;
}



void ATDEnemy::TDSetAnimMontaje(UAnimMontage* _montageRef)
{
    montageRef = _montageRef;
}

void ATDEnemy::TDSetActive_Implementation()
{
    isActive = true;
    TDInitialize();
    ATDEnemyController* controllerRef = GetController<ATDEnemyController>();
    controllerRef->GetBrainComponent()->StartLogic();
    GetMesh()->SetVisibility(true, true);
    GetCapsuleComponent()->SetCollisionProfileName(FName(TEXT("EnemyPawn")));
    GetCharacterMovement()->GravityScale = 1.f;
    SetActorTickEnabled(true);
    FGameplayEventData abilityData;
    UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this, GET_GAMEPLAY_TAG(INMORTAL_TRIGGER_TAG), abilityData);
    if (healthBar)
    {
        healthBar->SetVisibility(ESlateVisibility::Visible);
        FOnHealthChangeDelegate.Broadcast(1.f, 0.f);
    }
}

void ATDEnemy::TDSetDisable_Implementation()
{
    isActive = false;
    SetActorTickEnabled(false);


    ATDEnemyController* controllerRef = GetController<ATDEnemyController>();
    controllerRef->GetBrainComponent()->StopLogic(FString::SanitizeFloat(5.f));
    GetMesh()->SetVisibility(false, true);
    GetCapsuleComponent()->SetCollisionProfileName(FName(TEXT("NoCollision")));
    GetCharacterMovement()->GravityScale = 0.f;
    SetActorLocation(FVector(0.f, 0.f, -10000.f));

    if (healthBar)
    {
        healthBar->SetVisibility(ESlateVisibility::Collapsed);
    }
}

const bool ATDEnemy::TDGetActiveState()
{
    return isActive;
}

UTDHealthBar* ATDEnemy::TDGetHealthBarReference()
{
    return healthBar;
}

UWidgetComponent* ATDEnemy::TDGetHealthWidgetComponent()
{
    return widgetComponent;
}

UDataTable* ATDEnemy::TDGetLootDataTable() const
{
    return lootDataTable;
}

void ATDEnemy::TDSetLootDataTable(UDataTable* val)
{
    lootDataTable = val;
}

UDataTable* ATDEnemy::TDGetChanceDataTable() const
{
    return chanceDataTable;
}

void ATDEnemy::TDSetChanceDataTable(UDataTable* val)
{
    chanceDataTable = val;
}

void ATDEnemy::BeginPlay()
{
    Super::BeginPlay();
    SetActorTickEnabled(false);

    if (widgetComponent)
    {
        healthBar = Cast<UTDHealthBar>(widgetComponent->GetUserWidgetObject());

        if (healthBar)
        {
            FOnHealthChangeDelegate.AddDynamic(healthBar, &UTDHealthBar::TDSetBarPercentage);
        }
    }
}

void ATDEnemy::TDInitialize()
{
    Super::TDInitialize();



    FGameplayTagContainer tags;
    TArray<FActiveGameplayEffectHandle> effectsActive;
    effectsActive = abilitySystem->GetActiveEffectsWithAllTags(tags);
    for (FActiveGameplayEffectHandle iter : effectsActive)
    {
        abilitySystem->RemoveActiveGameplayEffect(iter);
    }
    abilitySystem->ClearAllAbilities();
    abilitySystem->RemoveAllSpawnedAttributes();


    const UAttributeSet* attributesInit1 = abilitySystem->InitStats(UTDHealthAttributeSet::StaticClass(), nullptr);

    healthAttributes = Cast<UTDHealthAttributeSet>(attributesInit1);

    const UAttributeSet* attributesInit2 = abilitySystem->InitStats(UTDDamageAttributeSet::StaticClass(), nullptr);
    damageAttributes = Cast<UTDDamageAttributeSet>(attributesInit2);

    const UAttributeSet* attributesInit3 = abilitySystem->InitStats(UTDMovementAttributeSet::StaticClass(), nullptr);
    movementAttributes = Cast<UTDMovementAttributeSet>(attributesInit3);

    TDCreateAndApplyGE();

    for (size_t i = 0; i < abiliyList.Num(); ++i)
    {
        FGameplayAbilitySpecHandle specHandle = abilitySystem->GiveAbility(FGameplayAbilitySpec(abiliyList[i].GetDefaultObject(), 1, 0));
    }
    float randomValue = FMath::FRandRange(-movementVariation, movementVariation);

    if (weaponAssetRef && weaponAssetRef->WeaponRange != 0.f)
    {
        UTDGameData::TDCreateAndApplyGE(abilitySystem, UTDDamageAttributeSet::GetattackRangeAttribute(), EGameplayModOp::Override, weaponAssetRef->WeaponRange);
    }

    if (weaponAssetRef)
    {
        abilitySystem->GiveAbility(FGameplayAbilitySpec(weaponAssetRef->weaponAbility.GetDefaultObject(), 1, 0));

    }



    GetCharacterMovement()->MaxWalkSpeed = movementAttributes->GetmovementSpeed() + randomValue;

    TDActivateDelegates();
}

void ATDEnemy::TDCreateAndApplyGE()
{
    UGameplayEffect* staticEffect = NewObject<UGameplayEffect>();

    FGameplayEffectExecutionDefinition modif;
    modif.CalculationClass = enemyAttribute;
    staticEffect->Executions.Add(modif);
    abilitySystem->ApplyGameplayEffectToTarget(staticEffect, abilitySystem);
    staticEffect->ConditionalBeginDestroy();
}

