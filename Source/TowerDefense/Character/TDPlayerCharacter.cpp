// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TDPlayerCharacter.h"
#include "GameLogic/TDGameData.h"

ATDPlayerCharacter::ATDPlayerCharacter()
{


    SwordMesh = CreateDefaultSubobject<UStaticMeshComponent>("SwordMesh");
    SwordMesh->SetupAttachment(GetMesh(), "WeaponSocketHero");

}

void ATDPlayerCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);


}

void ATDPlayerCharacter::TDUpdateRoundValues(int32 _Rounds)
{
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Player Update"));
}

void ATDPlayerCharacter::BeginPlay()
{
    Super::BeginPlay();

    TDInitialize();

    UTDGameData::TDGetRoundManager()->FOnBuyPhaseStartDelegate.AddDynamic(this, &ATDPlayerCharacter::TDUpdateRoundValues);
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


