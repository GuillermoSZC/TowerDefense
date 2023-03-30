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

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability System")
        TArray<TSubclassOf<UGameplayAbility>> abiliyList;


    UPROPERTY(VisibleAnywhere)
        TArray<ATDPathPoint*> PathPointsArray;


    UPROPERTY(EditAnywhere, Category = "Spawn Configuration")
        float movementVariation = 100.f;

    UPROPERTY(EditAnywhere, Category = "Spawn Configuration")
        int unitWeight = 1.f;


protected:


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


    UFUNCTION()
    void TDSetActive();

    UFUNCTION()
    void TDSetDisable();

    virtual void TDCharacterDeath_Implementation() override;


protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

private:


    void TDInitialize();
    

    



};
