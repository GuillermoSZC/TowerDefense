#include "Character/TDEnemy.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GameLogic/TDGameData.h"
#include "TDEnemyAttributeSet.h"
#include "GameplayTagContainer.h"
#include "TDMacros.h"
#include "GameLogic/TDPathPoint.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Map/TDBase.h"
#include "Components/CapsuleComponent.h"
#include "TDEnemyController.h"
#include "AIModule/Classes/BrainComponent.h"
#include "GameLogic/TDObjectPooler.h"


ATDEnemy::ATDEnemy()
{
    PrimaryActorTick.bCanEverTick = true;

    refreshPathTime = 0.2f;
    tickCounterTime = 0.f;

    abilitySystem = CreateDefaultSubobject<UAbilitySystemComponent>("AbilityComponent");


}

void ATDEnemy::TDCharacterDeath_Implementation()
{
    ATDObjectPooler::TDGetObjectPooler()->TDAddEnemyToPool(this);
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
}

void ATDEnemy::TDSetDisable()
{
    isActive = false;
    abilitySystem->ClearAllAbilities();
    abilitySystem->RemoveAllSpawnedAttributes();
    UTDGameData::TDRemoveEnmemyToArray(this);
    ATDEnemyController* controllerRef = GetController<ATDEnemyController>();
    controllerRef->GetBrainComponent()->StopLogic(FString::SanitizeFloat(5.f));    
    GetMesh()->SetVisibility(false, true);
    GetCapsuleComponent()->SetCollisionProfileName(FName(TEXT("NoCollision")));
    GetCharacterMovement()->GravityScale = 0.f;
    SetActorLocation(FVector(0.f,0.f,-10000.f));
}

void ATDEnemy::BeginPlay()
{
    Super::BeginPlay();

   
}

void ATDEnemy::TDInitialize()
{  
    const UAttributeSet* attributesInit = abilitySystem->InitStats(UTDEnemyAttributeSet::StaticClass(), statsDatatable);
    EnemyAttributes = Cast<UTDEnemyAttributeSet>(attributesInit);
    for (size_t i = 0; i < abiliyList.Num(); ++i)
    {
        FGameplayAbilitySpecHandle specHandle = abilitySystem->GiveAbility(FGameplayAbilitySpec(abiliyList[i].GetDefaultObject(), 1, 0));
    }
    float randomValue = FMath::FRandRange(-movementVariation, movementVariation);
    GetCharacterMovement()->MaxWalkSpeed = EnemyAttributes->GetmovementSpeed() + randomValue;

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

        UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this, GET_GAMEPLAY_TAG(DEATH_TRIGGER_TAG), DataEvent);
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

