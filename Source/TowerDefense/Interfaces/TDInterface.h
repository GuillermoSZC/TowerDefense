// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include <GameplayTagContainer.h>
#include "TDInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UTDInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 *
 */
class TOWERDEFENSE_API ITDInterface
{
    GENERATED_BODY()

        // Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:


    //Este se puede implementar en BP y en C++
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
        int TGGApplyEffect();

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
        void TDResetAttackTimer();

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
        UAnimMontage* TDGetSketalMeshMontage();

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
        void TDCharacterDeath();


    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
        UTDElementComponent* TDGetElementComponent();


    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
        void TDSetTemporalElement(EElements _newElement);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
        void TDRemoveTemporalElement();


    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
        bool TDIsDebugActive() const;


    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
        void TDRotateHeadTower(const FVector& _PositionToLook);


    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
        FVector TDGetShootPosition();


    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
        FGameplayTag TDGetTagClass();


    //Este solo se puede implementar en BP
//     UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
//         const bool TGGApplyEffect2() const;






};
