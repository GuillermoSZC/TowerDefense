// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/TDInterface.h"
#include "GameplayEffectTypes.h"
#include "Delegates/TDDeclareDelegates.h"
#include "TDCharacter.generated.h"




class UTDHealthAttributeSet;
class UTDDamageAttributeSet;
class UTDMovementAttributeSet;

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


      UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability System")
        UDataTable* healthDatatable;

      
        UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability System")
        UDataTable* damageDatatable;


           UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability System")
        UDataTable* movementDatatable;


                UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability System")
           FGameplayTag ClassTag;

           UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability System")
           TArray<FGameplayTag> TagsToAdd;



    FOnHealthChangeSignature FOnHealthChangeDelegate;
    
protected:

#pragma region DELEGATES

    FDelegateHandle HealthChangedDelegateHandle;
    FDelegateHandle AttackDamageChangedDelegateHandle;
    FDelegateHandle AttackRangeChangedDelegateHandle;
    FDelegateHandle AttackSpeedChangedDelegateHandle;
    FDelegateHandle MovementSpeedChangedDelegateHandle;
    FDelegateHandle BaseAttackSpeedChangedDelegateHandle;
    FDelegateHandle PercentageAttackSpeedChangedDelegateHandle;

#pragma endregion




      
    
    UPROPERTY(Transient)
        const UTDHealthAttributeSet* healthAttributes;    

    UPROPERTY(Transient)
        const UTDDamageAttributeSet* damageAttributes;    
     
    UPROPERTY(Transient)
        const UTDMovementAttributeSet* movementAttributes;





       UPROPERTY(EditAnywhere,BlueprintReadWrite)
    UTDElementComponent* elementComponent = nullptr;


private:


   


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


     UFUNCTION()
    virtual UTDElementComponent* TDGetElementComponent_Implementation() override;


     bool TDIsDebugActive_Implementation() const override;

         UFUNCTION(BlueprintNativeEvent)
     void TDOnElementChange(EElements _newElement);

         UFUNCTION()
         FGameplayTag TDGetTagClass_Implementation() override;



         void PostInitializeComponents() override;

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    void TDActivateDelegates();

    virtual void TDInitialize();

private:


    


    void TDmaxHealthChanged(const FOnAttributeChangeData& Data);
    void TDHealthChanged(const FOnAttributeChangeData& Data);
    void TDAttackDamageChanged(const FOnAttributeChangeData& Data);
    void TDAttackRangeChanged(const FOnAttributeChangeData& Data);
    void TDAttackSpeedChanged(const FOnAttributeChangeData& Data);
    void TDBaseAttackSpeedChanged(const FOnAttributeChangeData& Data);
    void TDPercentageSpeedChanged(const FOnAttributeChangeData& Data);
    void TDMovementSpeedChanged(const FOnAttributeChangeData& Data);

};
