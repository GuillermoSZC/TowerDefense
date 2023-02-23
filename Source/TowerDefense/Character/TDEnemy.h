#pragma once

#include "CoreMinimal.h"
#include "Character/TDPlayerCharacter.h"
#include "GameplayEffectTypes.h"
#include "GameplayTagContainer.h"
#include "TDEnemy.generated.h"

class UAbilitySystemComponent;
class UGameplayAbility;
class UDataTable;
class UTDEnemyAttributeSet;

UCLASS()
class TOWERDEFENSE_API ATDEnemy : public ATDPlayerCharacter
{
    GENERATED_BODY()
public:
    ATDEnemy();

public:


    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability System")
        UDataTable* statsDatatable;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability System")
        TArray<TSubclassOf<UGameplayAbility>> abiliyList;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ability System", meta = (AllowPrivateAccess = "true"))
        UAbilitySystemComponent* abilitySystem;


    FGameplayTag tag;

protected:


#pragma region DELEGATES

    FDelegateHandle EnemyHealthChangedDelegateHandle;
    FDelegateHandle EnemyAttackDamageChangedDelegateHandle;
    FDelegateHandle EnemyAttackRangeChangedDelegateHandle;
    FDelegateHandle EnemyAttackSpeedChangedDelegateHandle;
    FDelegateHandle EnemyMovementSpeedChangedDelegateHandle;


#pragma endregion


private:

    float refreshPathTime;
    float tickCounterTime;
    float pathDsitance;


    UPROPERTY(Transient)
    const UTDEnemyAttributeSet* EnemyAttributes;


public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;


    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
        float TDCalculatePathDistance();

    UFUNCTION(BlueprintCallable)
        float TDGetPathDistance();


protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

private:


    void TDInitialize();
    void TDActivateDelegates();

    void TDmaxHealthChanged(const FOnAttributeChangeData& Data);
    void TDHealthChanged(const FOnAttributeChangeData& Data);
    void TDAttackDamageChanged(const FOnAttributeChangeData& Data);
    void TDAttackRangeChanged(const FOnAttributeChangeData& Data);
    void TDAttackSpeedChanged(const FOnAttributeChangeData& Data);
    void TDMovementSpeedChanged(const FOnAttributeChangeData& Data);




};
