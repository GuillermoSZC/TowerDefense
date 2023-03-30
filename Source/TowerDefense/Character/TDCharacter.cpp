// Fill out your copyright notice in the Description page of Project Settings.


#include "TDCharacter.h"
#include "TDCharacterAttributeSet.h"
#include "TDMacros.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AttributesSets/TDMovementAttributeSet.h"
#include "AttributesSets/TDDamageAttributeSet.h"
#include "AttributesSets/TDHealthAttributeSet.h"




// Sets default values
ATDCharacter::ATDCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


    abilitySystem = CreateDefaultSubobject<UAbilitySystemComponent>("AbilityComponent");
    elementComponent = CreateDefaultSubobject<UTDElementComponent>("ElementComponent");

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



void ATDCharacter::TDActivateDelegates()
{
    abilitySystem->GetGameplayAttributeValueChangeDelegate(healthAttributes->GethealthAttribute()).AddUObject(this, &ATDCharacter::TDHealthChanged);
    abilitySystem->GetGameplayAttributeValueChangeDelegate(healthAttributes->GetmaxHealthAttribute()).AddUObject(this, &ATDCharacter::TDmaxHealthChanged);
    abilitySystem->GetGameplayAttributeValueChangeDelegate(damageAttributes->GetattackDamageAttribute()).AddUObject(this, &ATDCharacter::TDAttackDamageChanged);
    abilitySystem->GetGameplayAttributeValueChangeDelegate(damageAttributes->GetattackRangeAttribute()).AddUObject(this, &ATDCharacter::TDAttackRangeChanged);
    abilitySystem->GetGameplayAttributeValueChangeDelegate(damageAttributes->GetattackSpeedAttribute()).AddUObject(this, &ATDCharacter::TDAttackSpeedChanged);
    abilitySystem->GetGameplayAttributeValueChangeDelegate(movementAttributes->GetmovementSpeedAttribute()).AddUObject(this, &ATDCharacter::TDMovementSpeedChanged);
}

void ATDCharacter::TDmaxHealthChanged(const FOnAttributeChangeData& Data)
{

}

void ATDCharacter::TDHealthChanged(const FOnAttributeChangeData& Data)
{
    if (Data.NewValue <= 0.f)
    {
        FGameplayEventData DataEvent;
        UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this, GET_GAMEPLAY_TAG(DEATH_TRIGGER_TAG), DataEvent);
    }

    float MaxHealth = healthAttributes->GetmaxHealth();
    float healthPercent = Data.NewValue / MaxHealth;
    FOnHealthChangeDelegate.Broadcast(healthPercent);
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

void ATDCharacter::TDMovementSpeedChanged(const FOnAttributeChangeData& Data)
{

}
