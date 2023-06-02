// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "TDPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class ATDCharacter;
class UTDPauseMenu;

/**
 *
 */
UCLASS()
class TOWERDEFENSE_API ATDPlayerController : public APlayerController
{
    GENERATED_BODY()


public:

    ATDPlayerController();

public:

    UPROPERTY(EditDefaultsOnly)
        UInputMappingContext* DefaultMappingContext;

    UPROPERTY(EditDefaultsOnly)
        UInputAction* MoveForwardInputAction;

    UPROPERTY(EditDefaultsOnly)
        UInputAction* MoveSideInputAction;

    UPROPERTY(EditDefaultsOnly)
        UInputAction* HitActionInputAction;

    UPROPERTY(EditDefaultsOnly)
        UInputAction* PauseInputAction;

    UPROPERTY(EditDefaultsOnly)
        TSubclassOf<UTDPauseMenu> pauseMenuClass;

protected:
    UPROPERTY()
        UTDPauseMenu* pauseMenuRef;

private:

    UPROPERTY(Transient)
        ATDCharacter* playerPawn;

public:

    UFUNCTION()
        void TDOnOpenUI(UWidget* _widgetRef);
    UFUNCTION()
        void TDOnCloseUI();



protected:



    virtual void BeginPlay() override;


private:


    void TDMoveForwardAction(const FInputActionValue& _value);
    void TDMoveSideAction(const FInputActionValue& _value);
    void TDHitAction(const FInputActionValue& _value);
    void TDOpenPauseMenu(const FInputActionValue& _value);

    UFUNCTION()
        void TDOnBuyPhaseStart(int32 _num);

    UFUNCTION()
        void TDOnCombatPhaseStart(int32 _num);
};
