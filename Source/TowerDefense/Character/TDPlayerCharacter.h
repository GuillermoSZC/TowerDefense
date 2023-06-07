// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/TDCharacter.h"
#include "GameLogic/TDLootEnum.h"
#include <GameplayEffect.h>
#include "TDPlayerCharacter.generated.h"

class UNiagaraComponent;

/**
 *
 */
UCLASS()
class TOWERDEFENSE_API ATDPlayerCharacter : public ATDCharacter
{
    GENERATED_BODY()

public:
    ATDPlayerCharacter();

public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability System")
        UDataTable* statsDatatable;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability System")
        TArray<TSubclassOf<UGameplayAbility>> abiliyList;

        UPROPERTY(EditDefaultsOnly, Category = "Ability System",meta =( DisplayName = "Effect To Apply at the end of Combat Phase"))
        TSubclassOf<UGameplayEffect> EffectClass;


    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        UStaticMeshComponent* SwordMesh;


    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Element VFX")
        TMap<EElements, UTDElementVFXDataAsset*> ElementsVFX;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        UNiagaraComponent* swordCover;


protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Loot Inventory")
        TMap<ELootItems, int32> PlayerInventory;


    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Element VFX")
        UTDElementVFXDataAsset* actualVFXAsset = nullptr;

private:

    UPROPERTY(Transient)
    UGameplayEffect* effectRef;

public:

    virtual void Tick(float DeltaTime) override;

    UFUNCTION()
        void TDUpdateRoundValues(int32 _Rounds);

    UFUNCTION(BlueprintPure)
        int32 TDGetAmountItemByItem(ELootItems _item);

    UFUNCTION(BlueprintCallable)
        int32 TDAddItemToInventory(ELootItems _item, int32 _amount = 1);

    UFUNCTION(BlueprintCallable)
        void TDOverrideItemInInventory(ELootItems _item, int32 _newValue);


    UFUNCTION(BlueprintPure)
        TMap<ELootItems, int32>& TDGetPlayerInventory();


    UFUNCTION(BlueprintPure)
        UTDElementVFXDataAsset* TDGetActualElementVFXAsset();


protected:

    virtual void BeginPlay() override;


    void TDInitialize();

    void TDOnElementChange_Implementation(EElements _newElement) override;



private:


    void PostInitializeComponents() override;

};
