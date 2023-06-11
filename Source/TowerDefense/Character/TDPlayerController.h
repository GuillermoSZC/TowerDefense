// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include <EnhancedInputComponent.h>

#include "TDPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class ATDCharacter;
class UTDPauseMenu;
class UTDCostWidget;
class UTDPlayerHUD;

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
        UInputMappingContext* BuyPhaseMappingContext;

    UPROPERTY(EditDefaultsOnly)
        UInputMappingContext* CombatPhaseMappingContext;

    UPROPERTY(EditDefaultsOnly)
        UInputAction* MoveForwardInputAction;

    UPROPERTY(EditDefaultsOnly)
        UInputAction* MoveSideInputAction;

    UPROPERTY(EditDefaultsOnly)
        UInputAction* HitActionInputAction;

    UPROPERTY(EditDefaultsOnly)
        UInputAction* PauseInputAction;

    UPROPERTY(EditDefaultsOnly)
        UInputAction* TraceInputAction;

    UPROPERTY(EditDefaultsOnly)
        TSubclassOf<UTDPauseMenu> pauseMenuClass;

    UPROPERTY(EditDefaultsOnly)
        TSubclassOf<UTDPlayerHUD> playerHUDClass;


    UPROPERTY(EditDefaultsOnly, Category = "Trace")
        float lenghtTrace = 100000.f;

    UPROPERTY(EditDefaultsOnly, Category = "Trace");
    TEnumAsByte<ECollisionChannel> traceChannel;

protected:
    UPROPERTY(Transient)
        UTDPauseMenu* pauseMenuRef;

    UPROPERTY(Transient)
        UTDPlayerHUD* playerHUDRef;

    FInputActionBinding traceBind = FInputActionBinding();


private:
    UPROPERTY(Transient)
        ATDCharacter* playerPawn;

    UPROPERTY(Transient)
        UTDCostWidget* costWidgetRef;



public:
    UFUNCTION()
        void TDOnOpenUI(UTDCostWidget* _widgetRef);

    UFUNCTION()
        void TDOnCloseUI();

    UFUNCTION()
        UTDPlayerHUD* TDGetPLayerHUD();

protected:
    virtual void BeginPlay() override;


private:
    UFUNCTION()
        void TDMoveForwardAction(const FInputActionValue& _value);

    UFUNCTION()
        void TDMoveSideAction(const FInputActionValue& _value);

    UFUNCTION()
        void TDHitAction(const FInputActionValue& _value);

    UFUNCTION()
        void TDChangePauseMenuVisibility(const FInputActionValue& _value);

    UFUNCTION()
        void TDClosePauseMenu();

    UFUNCTION()
        void TDPauseMenuLogic(ESlateVisibility _visibility, bool _value);

    UFUNCTION()
        void TDOnBuyPhaseStart(int32 _num);

    void TDChangeToAvalibleTrace();
    void TDChangeNotToAvalibleTrace();


    UFUNCTION()
        void TDOnCombatPhaseStart(int32 _num);

    UFUNCTION()
        void TDTraceFromCameraToOpenUI(const FInputActionValue& _value);
};