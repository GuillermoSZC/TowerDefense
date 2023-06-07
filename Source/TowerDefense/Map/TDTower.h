// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/TDInterface.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffectTypes.h"
#include "Delegates/TDDeclareDelegates.h"
#include "InputCoreTypes.h"
#include "Interfaces/TDCostInterface.h"
#include <GameplayEffect.h>
#include "TDTower.generated.h"

class UTDTowerAttributeSet;
class UDataTable;
class UTDDamageAttributeSet;
class UTDTowerUpgrade;
class UTDWidgetShopComponent;

UCLASS()
class TOWERDEFENSE_API ATDTower : public AActor, public ITDInterface, public IAbilitySystemInterface, public ITDCostInterface
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ATDTower();

public:

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability System")
        UDataTable* damageDatatable;

    UPROPERTY(EditAnywhere, BlueprintReadWrite) // @TODO: Pasar a privado?
        UTDElementComponent* elementComponent = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability System")
        TArray<TSubclassOf<class UGameplayAbility>> abiliyList;

    UPROPERTY(BlueprintAssignable)
        FOnAttackRangeChangeSignature FOnAttackRangeChangeDelegate;

    UPROPERTY(BlueprintAssignable)
    FOnLevelUpChangeSignature FOnLevelUpChangeDelegate;


    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability System")
        FGameplayTag TagClass;


    UPROPERTY(EditDefaultsOnly, Category = "Ability System", meta = (DisplayName = "Upgrade Every X Level"))
        int32 UpgradeEveryXLevel;

    UPROPERTY(EditDefaultsOnly, Category = "Ability System")
        TSubclassOf<UGameplayEffect> levelUpgrade;


    UPROPERTY(EditAnywhere)
    UTDWidgetShopComponent* widgetShopRef;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ability System", meta = (AllowPrivateAccess = "true"))
        UAbilitySystemComponent* abilitySystem;



#pragma region DELEGATES


    FDelegateHandle TowerRangeChangedDelegateHandle;
    FDelegateHandle TowerDamageChangedDelegateHandle;
    FDelegateHandle TowerPeriodAttackChangedDelegateHandle;
    FDelegateHandle TowerBaseAttackSpeedChangedDelegateHandle;
    FDelegateHandle TowerPercentageAttackSpeedChangedDelegateHandle;
    FDelegateHandle LevelUpChangedDelegateHandle;
#pragma endregion


    UPROPERTY(EditDefaultsOnly)
        ELootItems BPToUprgade;

private:
    UPROPERTY()
        float timer;

    UPROPERTY()
        float periodAttack;

    UPROPERTY(Transient)
        const UTDDamageAttributeSet* TowerAttributes;



public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    UFUNCTION()
        int TGGApplyEffect_Implementation();


    UFUNCTION(BlueprintCallable)
        ATDEnemy* TDGetEnemyInRange();

    UFUNCTION()
        void TDUpdateRoundValues(int32 _Round);


    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
        void TDActivateAction();

    UFUNCTION()
        void TDResetAttackTimer_Implementation() override;

    virtual UTDElementComponent* TDGetElementComponent_Implementation() override;

    UFUNCTION(BlueprintPure)
        bool TDIsDebugActive_Implementation() const override;

    UFUNCTION(BlueprintNativeEvent)
        void TDOnElementChange(EElements _newElement);




    UFUNCTION(BlueprintCallable)
        UAbilitySystemComponent* GetAbilitySystemComponent() const override;

    //Gems
    void TDCalculateElementChangeCost_Implementation(FBuyCost& _cost, ELootItems _itemElement) override;

    //BPs
    void TDCalcultateCostWithLoot_Implementation(FBuyCost& _cost, ELootItems _item = ELootItems::None) override;

    bool TDCanAffordCostWithLoot_Implementation(FBuyCost& _cost) override;

    bool TDCommitBuyUpgrade_Implementation(ELootItems _item = ELootItems::None) override;

    UFUNCTION()
        FGameplayTag TDGetTagClass_Implementation() override;


    UFUNCTION(BlueprintPure)
        ELootItems TDGetItemToUpgrade();


    void TDTriggerOpenUI() override;

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;


private:

    void TDInitialize();

    void TDActivateDelegates();

    void TDDamageChanged(const FOnAttributeChangeData& Data);


    void TDRangeChanged(const FOnAttributeChangeData& Data);

    void TDPeriodAttackChanged(const FOnAttributeChangeData& Data);

    void TDLevelUpChanged(const FOnAttributeChangeData& Data);

    void TDPercentageSpeedChanged(const FOnAttributeChangeData& Data);

    void TDBaseAttackSpeedChanged(const FOnAttributeChangeData& Data);

};
