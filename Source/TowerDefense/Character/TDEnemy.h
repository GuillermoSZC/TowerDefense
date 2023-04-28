#pragma once

#include "CoreMinimal.h"
#include "Character/TDCharacter.h"
#include "GameplayEffectTypes.h"

#include "TDEnemy.generated.h"

class UAbilitySystemComponent;
class UGameplayAbility;
class UDataTable;
class UTDEnemyAttributeSet;
class ATDPathPoint;

UCLASS()
class TOWERDEFENSE_API ATDEnemy : public ATDCharacter
{
    GENERATED_BODY()
public:
    ATDEnemy();

public:


      UPROPERTY(BlueprintReadOnly)
    FString DebugString;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability System")
        TArray<TSubclassOf<UGameplayAbility>> abiliyList;


    UPROPERTY(VisibleAnywhere)
        TArray<ATDPathPoint*> PathPointsArray;

     

    UPROPERTY(EditAnywhere, Category = "Spawn Configuration")
        float movementVariation = 100.f;

    UPROPERTY(EditAnywhere, Category = "Spawn Configuration")
        int unitWeight = 1.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    USkeletalMeshComponent* skeletalWeaponComponent;

    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMeshComponent* StaticWeaponComponent;


protected:
    UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "HUD")
        class UWidgetComponent* widgetComponent;

    UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "HUD")
        class UTDHealthBar* healthBar;


private:

    float refreshPathTime;
    float tickCounterTime;
    float pathDsitance;

    UPROPERTY()
        bool isActive = false;



    UPROPERTY(Transient)
        UAnimMontage* montageRef = nullptr;




public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;


    UFUNCTION(BlueprintCallable)
        float TDCalculatePathDistance();

    UFUNCTION(BlueprintCallable)
        float TDGetPathDistance();

    UFUNCTION(BlueprintCallable)
        void TDSetPath(ATDPathPoint* _pathPointRef);

    UFUNCTION()
        ATDPathPoint* TDGetNextPathPoint();

    UFUNCTION()
        void TDSetAnimMontaje(UAnimMontage* _montageRef);

    virtual UAnimMontage* TDGetSketalMeshMontage_Implementation() override;

    UFUNCTION(BlueprintNativeEvent)
        void TDSetActive();

    UFUNCTION(BlueprintNativeEvent)
        void TDSetDisable();

    UFUNCTION(BlueprintPure)
    const bool TDGetActiveState();

    virtual void TDCharacterDeath_Implementation() override;

    UFUNCTION(BlueprintCallable)
        class UTDHealthBar* TDGetHealthBarReference();

    UFUNCTION(BlueprintCallable)
        class UWidgetComponent* TDGetHealthWidgetComponent();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    virtual void TDInitialize() override;

private:

   






};
