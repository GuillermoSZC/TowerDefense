// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/TDInterface.h"
#include "TDCharacter.generated.h"

class UTDCharacterAttributeSet;

UCLASS()
class TOWERDEFENSE_API ATDCharacter : public ACharacter, public ITDInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATDCharacter();


public:

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ability System", meta = (AllowPrivateAccess = "true"))
        UAbilitySystemComponent* abilitySystem;


protected:

#pragma region DELEGATES

    FDelegateHandle HealthChangedDelegateHandle;
    FDelegateHandle AttackDamageChangedDelegateHandle;
    FDelegateHandle AttackRangeChangedDelegateHandle;
    FDelegateHandle AttackSpeedChangedDelegateHandle;
    FDelegateHandle MovementSpeedChangedDelegateHandle;


#pragma endregion


    UPROPERTY(Transient)
        const UTDCharacterAttributeSet* CharacterAttributes;

private:





public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    void TDActivateDelegates();

private:





    void TDmaxHealthChanged(const FOnAttributeChangeData& Data);
    void TDHealthChanged(const FOnAttributeChangeData& Data);
    void TDAttackDamageChanged(const FOnAttributeChangeData& Data);
    void TDAttackRangeChanged(const FOnAttributeChangeData& Data);
    void TDAttackSpeedChanged(const FOnAttributeChangeData& Data);
    void TDMovementSpeedChanged(const FOnAttributeChangeData& Data);

};
