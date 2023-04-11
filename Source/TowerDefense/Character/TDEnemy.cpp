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


ATDEnemy::ATDEnemy()
{
    PrimaryActorTick.bCanEverTick = true;

    refreshPathTime = 0.2f;
    tickCounterTime = 0.f;

    widgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
    widgetComponent->SetupAttachment(RootComponent);
}



void ATDEnemy::TDCharacterDeath_Implementation()
{
    UTDGameData::TDGetObjectPooler()->TDAddEnemyToPool(this);
    TDSetDisable();
    UTDGameData::TDRemoveEnmemyToArray(this);

}

UAnimMontage* ATDEnemy::TDGetSketalMeshMontage_Implementation()
{
    return montageRef;
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

void ATDEnemy::TDSetActive()
{
    isActive = true;
    TDInitialize();
    UTDGameData::TDAddEnmemyToArray(this);
    ATDEnemyController* controllerRef = GetController<ATDEnemyController>();
    controllerRef->GetBrainComponent()->StartLogic();
    GetMesh()->SetVisibility(true, true);
    GetCapsuleComponent()->SetCollisionProfileName(FName(TEXT("EnemyPawn")));
    GetCharacterMovement()->GravityScale = 1.f;

    if (healthBar)
    {
        healthBar->SetVisibility(ESlateVisibility::Visible);
    }
}

void ATDEnemy::TDSetDisable()
{
    isActive = false;

    FGameplayTagContainer tags;
    TArray<FActiveGameplayEffectHandle> effectsActive;
    effectsActive = abilitySystem->GetActiveEffectsWithAllTags(tags);
    for (FActiveGameplayEffectHandle iter : effectsActive)
    {
        abilitySystem->RemoveActiveGameplayEffect(iter);
    }
    abilitySystem->ClearAllAbilities();
    abilitySystem->RemoveAllSpawnedAttributes();
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

UTDHealthBar* ATDEnemy::TDGetHealthBarReference()
{
    return healthBar;
}

UWidgetComponent* ATDEnemy::TDGetHealthWidgetComponent()
{
    return widgetComponent;
}

void ATDEnemy::BeginPlay()
{
    Super::BeginPlay();

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

    const UAttributeSet* attributesInit1 = abilitySystem->InitStats(UTDHealthAttributeSet::StaticClass(), healthDatatable);
    healthAttributes = Cast<UTDHealthAttributeSet>(attributesInit1);

    const UAttributeSet* attributesInit2 = abilitySystem->InitStats(UTDDamageAttributeSet::StaticClass(), damageDatatable);
    damageAttributes = Cast<UTDDamageAttributeSet>(attributesInit2);

    const UAttributeSet* attributesInit3 = abilitySystem->InitStats(UTDMovementAttributeSet::StaticClass(), movementDatatable);
    movementAttributes = Cast<UTDMovementAttributeSet>(attributesInit3);


    for (size_t i = 0; i < abiliyList.Num(); ++i)
    {
        FGameplayAbilitySpecHandle specHandle = abilitySystem->GiveAbility(FGameplayAbilitySpec(abiliyList[i].GetDefaultObject(), 1, 0));
    }
    float randomValue = FMath::FRandRange(-movementVariation, movementVariation);
    GetCharacterMovement()->MaxWalkSpeed = movementAttributes->GetmovementSpeed() + randomValue;

    TDActivateDelegates();
}


