// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TDPlayerCharacter.h"
#include "GameLogic/TDGameData.h"
#include "GameLogic/TDRoundManager.h"

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
    //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Player Update"));
}

void ATDPlayerCharacter::BeginPlay()
{
    Super::BeginPlay();

    TDInitialize();

    UTDGameData::TDGetRoundManager()->FOnBuyPhaseStartDelegate.AddDynamic(this, &ATDPlayerCharacter::TDUpdateRoundValues);
}


void ATDPlayerCharacter::TDInitialize()
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
    GetCharacterMovement()->MaxWalkSpeed = movementAttributes->GetmovementSpeed();

    TDActivateDelegates();
}


