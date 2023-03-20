// Fill out your copyright notice in the Description page of Project Settings.


#include "TDCharacter.h"
#include "TDCharacterAttributeSet.h"
#include "TDMacros.h"
#include "AbilitySystemBlueprintLibrary.h"



// Sets default values
ATDCharacter::ATDCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


    abilitySystem = CreateDefaultSubobject<UAbilitySystemComponent>("AbilityComponent");


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
    abilitySystem->GetGameplayAttributeValueChangeDelegate(CharacterAttributes->GethealthAttribute()).AddUObject(this, &ATDCharacter::TDHealthChanged);
    abilitySystem->GetGameplayAttributeValueChangeDelegate(CharacterAttributes->GetmaxHealthAttribute()).AddUObject(this, &ATDCharacter::TDmaxHealthChanged);
    abilitySystem->GetGameplayAttributeValueChangeDelegate(CharacterAttributes->GetattackDamageAttribute()).AddUObject(this, &ATDCharacter::TDAttackDamageChanged);
    abilitySystem->GetGameplayAttributeValueChangeDelegate(CharacterAttributes->GetattackRangeAttribute()).AddUObject(this, &ATDCharacter::TDAttackRangeChanged);
    abilitySystem->GetGameplayAttributeValueChangeDelegate(CharacterAttributes->GetattackSpeedAttribute()).AddUObject(this, &ATDCharacter::TDAttackSpeedChanged);
    abilitySystem->GetGameplayAttributeValueChangeDelegate(CharacterAttributes->GetmovementSpeedAttribute()).AddUObject(this, &ATDCharacter::TDMovementSpeedChanged);
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

    float MaxHealth = CharacterAttributes->GetmaxHealth();
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
