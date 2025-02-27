// Fill out your copyright notice in the Description page of Project Settings.


#include "TDCharacter.h"
#include "TDMacros.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AttributesSets/TDMovementAttributeSet.h"
#include "AttributesSets/TDDamageAttributeSet.h"
#include "AttributesSets/TDHealthAttributeSet.h"
#include "GameLogic/TDElementComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Gas/TDGameplayEventData.h"




// Sets default values
ATDCharacter::ATDCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


    abilitySystem = CreateDefaultSubobject<UAbilitySystemComponent>("AbilityComponent");
    elementComponent = CreateDefaultSubobject<UTDElementComponent>("ElementComponent");

}



void ATDCharacter::PostInitializeComponents()
{
    Super::PostInitializeComponents();
    elementComponent->OnElementChangeDelegate.AddUniqueDynamic(this, &ATDCharacter::TDOnElementChange);

}

FGameplayTag ATDCharacter::TDGetTagClass_Implementation()
{
    return ClassTag;
}

UTDElementComponent* ATDCharacter::TDGetElementComponent_Implementation()
{
    return elementComponent;
}

// Called when the game starts or when spawned
void ATDCharacter::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ATDCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATDCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}



void ATDCharacter::TDOnElementChange_Implementation(EElements _newElement)
{

}

bool ATDCharacter::TDIsDebugActive_Implementation() const
{
    return false;
}


void ATDCharacter::TDActivateDelegates()
{
    abilitySystem->GetGameplayAttributeValueChangeDelegate(healthAttributes->GethealthAttribute()).AddUObject(this, &ATDCharacter::TDHealthChanged);
    abilitySystem->GetGameplayAttributeValueChangeDelegate(healthAttributes->GetmaxHealthAttribute()).AddUObject(this, &ATDCharacter::TDmaxHealthChanged);
    abilitySystem->GetGameplayAttributeValueChangeDelegate(damageAttributes->GetattackDamageAttribute()).AddUObject(this, &ATDCharacter::TDAttackDamageChanged);
    abilitySystem->GetGameplayAttributeValueChangeDelegate(damageAttributes->GetattackRangeAttribute()).AddUObject(this, &ATDCharacter::TDAttackRangeChanged);
    abilitySystem->GetGameplayAttributeValueChangeDelegate(damageAttributes->GetattackSpeedAttribute()).AddUObject(this, &ATDCharacter::TDAttackSpeedChanged);
    abilitySystem->GetGameplayAttributeValueChangeDelegate(damageAttributes->GetBaseAttackSpeedAttribute()).AddUObject(this, &ATDCharacter::TDBaseAttackSpeedChanged);
    abilitySystem->GetGameplayAttributeValueChangeDelegate(damageAttributes->GetPercentageAttackSpeedAttribute()).AddUObject(this, &ATDCharacter::TDPercentageSpeedChanged);
    abilitySystem->GetGameplayAttributeValueChangeDelegate(movementAttributes->GetmovementSpeedAttribute()).AddUObject(this, &ATDCharacter::TDMovementSpeedChanged);
}

void ATDCharacter::TDInitialize()
{
    for (FGameplayTag iter : TagsToAdd)
    {
        abilitySystem->AddLooseGameplayTag(iter);
    }
}

void ATDCharacter::TDmaxHealthChanged(const FOnAttributeChangeData& Data)
{
    float actualhealth = healthAttributes->Gethealth();
    float healthPercent = actualhealth / Data.NewValue;
    FOnHealthChangeDelegate.Broadcast(healthPercent,actualhealth);
}

void ATDCharacter::TDHealthChanged(const FOnAttributeChangeData& Data)
{
    if (Data.NewValue <= 0.f)
    {
        FGameplayEventData DataEvent;
        UTDGameplayEventData* data = NewObject<UTDGameplayEventData>(this, TEXT("GAMEDATA"));
        DataEvent.OptionalObject = data;
        data->VectorPosition = GetActorLocation();
        UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this, GET_GAMEPLAY_TAG(DEATH_TRIGGER_TAG), DataEvent);
    }

    float MaxHealth = healthAttributes->GetmaxHealth();
    float healthPercent = Data.NewValue / MaxHealth;
    FOnHealthChangeDelegate.Broadcast(healthPercent,Data.NewValue);
}

void ATDCharacter::TDAttackDamageChanged(const FOnAttributeChangeData& Data)
{

}

void ATDCharacter::TDAttackRangeChanged(const FOnAttributeChangeData& Data)
{

}

void ATDCharacter::TDAttackSpeedChanged(const FOnAttributeChangeData& Data)
{

}

void ATDCharacter::TDBaseAttackSpeedChanged(const FOnAttributeChangeData& Data)
{

}

void ATDCharacter::TDPercentageSpeedChanged(const FOnAttributeChangeData& Data)
{

}

void ATDCharacter::TDMovementSpeedChanged(const FOnAttributeChangeData& Data)
{
    GetCharacterMovement()->MaxWalkSpeed = Data.NewValue;
}
