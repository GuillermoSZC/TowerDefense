// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TDPlayerCharacter.h"

ATDPlayerCharacter::ATDPlayerCharacter()
{

}

void ATDPlayerCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);


}

void ATDPlayerCharacter::BeginPlay()
{
    Super::BeginPlay();


    TDInitialize();
}


void ATDPlayerCharacter::TDInitialize()
{
    const UAttributeSet* attributesInit = abilitySystem->InitStats(UTDCharacterAttributeSet::StaticClass(), statsDatatable);
    CharacterAttributes = Cast<UTDCharacterAttributeSet>(attributesInit);

    for (size_t i = 0; i < abiliyList.Num(); ++i)
    {
        FGameplayAbilitySpecHandle specHandle = abilitySystem->GiveAbility(FGameplayAbilitySpec(abiliyList[i].GetDefaultObject(), 1, 0));
    }
    GetCharacterMovement()->MaxWalkSpeed = CharacterAttributes->GetmovementSpeed();

    TDActivateDelegates();
}


