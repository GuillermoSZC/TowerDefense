// Fill out your copyright notice in the Description page of Project Settings.


#include "TDPlayerController.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "EnhancedInputComponent.h"
#include "TDMacros.h"
#include "TDCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "UMG/Public/Blueprint/WidgetBlueprintLibrary.h"
#include <Abilities/GameplayAbilityTypes.h>
#include <AbilitySystemBlueprintLibrary.h>
#include "GameLogic/TDRoundManager.h"
#include "GameLogic/TDGameData.h"
#include "UI/PauseMenu/TDPauseMenu.h"
#include <Kismet/GameplayStatics.h>


ATDPlayerController::ATDPlayerController()
{

}

void ATDPlayerController::BeginPlay()
{
    Super::BeginPlay();

    playerPawn = GetPawn<ATDCharacter>();

    UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
    if (Subsystem)
    {
        Subsystem->AddMappingContext(DefaultMappingContext, 0);

    }

    UTDGameData::TDGetRoundManager()->FOnBuyPhaseStartDelegate.AddDynamic(this, &ATDPlayerController::TDOnBuyPhaseStart);
    UTDGameData::TDGetRoundManager()->FOnCombatPhaseStartDelegate.AddDynamic(this, &ATDPlayerController::TDOnCombatPhaseStart);

    UEnhancedInputComponent* InputEnhanced = Cast<UEnhancedInputComponent>(InputComponent);

    InputEnhanced->BindAction(HitActionInputAction, ETriggerEvent::Triggered, this, &ATDPlayerController::TDHitAction);
    InputEnhanced->BindAction(MoveSideInputAction, ETriggerEvent::Triggered, this, &ATDPlayerController::TDMoveSideAction);
    InputEnhanced->BindAction(MoveForwardInputAction, ETriggerEvent::Triggered, this, &ATDPlayerController::TDMoveForwardAction);
    InputEnhanced->BindAction(PauseInputAction, ETriggerEvent::Triggered, this, &ATDPlayerController::TDOpenPauseMenu);
    PauseInputAction->bTriggerWhenPaused = true;

    if (pauseMenuClass)
    {
        pauseMenuRef = CreateWidget<UTDPauseMenu>(this, pauseMenuClass);

        if (pauseMenuRef)
        {
            pauseMenuRef->AddToViewport(1);
            pauseMenuRef->SetVisibility(ESlateVisibility::Collapsed);
        }
    }
}

void ATDPlayerController::TDMoveForwardAction(const FInputActionValue& _value)
{

    const float Magnitude = _value.GetMagnitude();
    if (Magnitude != 0.f)
    {
        // Find out which way is forward
        const FRotator Rotation = GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        // Get Forward Vector
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        playerPawn->AddMovementInput(Direction, Magnitude);
    }
}

void ATDPlayerController::TDMoveSideAction(const FInputActionValue& _value)
{


    const float Magnitude = _value.GetMagnitude();
    if (Magnitude != 0.f)
    {
        // Find out which way is forward
        const FRotator Rotation = GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        // Get Forward Vector
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
        playerPawn->AddMovementInput(Direction, Magnitude);
    }
}

void ATDPlayerController::TDHitAction(const FInputActionValue& _value)
{
    FGameplayEventData abilityData;
    UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(playerPawn, GET_GAMEPLAY_TAG(ABILITY1_TRIGGER_TAG), abilityData);
}

void ATDPlayerController::TDOpenPauseMenu(const FInputActionValue& _value)
{
    if (pauseMenuRef->GetVisibility() == ESlateVisibility::Collapsed)
    {
        TDPauseMenuLogic(ESlateVisibility::Visible, true);
    }
    else
    {
        TDPauseMenuLogic(ESlateVisibility::Collapsed, false);
    }
}

void ATDPlayerController::TDPauseMenuLogic(ESlateVisibility _visibility, bool _value)
{
    if (pauseMenuRef)
    {
        UGameplayStatics::SetGamePaused(GetWorld(), _value);

        if (_value)
        {
            FInputModeGameAndUI inputMode;
            inputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
            inputMode.SetWidgetToFocus(pauseMenuRef->TakeWidget());
            inputMode.SetHideCursorDuringCapture(false);
            SetInputMode(inputMode);
            bShowMouseCursor = true;
            bEnableClickEvents = false;
            bEnableTouchEvents = false;
        }
        else
        {
            FInputModeGameOnly inputMode;
            SetInputMode(inputMode);

            UTDGameData::TDGetRoundManager()->TDGetActualPhase() == GamePhase::BuyPhase ? TDOnBuyPhaseStart(0) : TDOnCombatPhaseStart(0);
        }

        pauseMenuRef->SetVisibility(_visibility);
    }
}

void ATDPlayerController::TDOnBuyPhaseStart(int32 _num)
{
    bEnableClickEvents = true;
    bShowMouseCursor = true;
    bEnableTouchEvents = true;
}

void ATDPlayerController::TDOnCombatPhaseStart(int32 _num)
{
    bEnableClickEvents = false;
    bShowMouseCursor = false;
    bEnableTouchEvents = false;
}

void ATDPlayerController::TDOnOpenUI(UWidget* _widgetRef)
{
    SetIgnoreMoveInput(true);
    SetIgnoreLookInput(true);

}

void ATDPlayerController::TDOnCloseUI()
{
    SetIgnoreMoveInput(false);
    SetIgnoreLookInput(false);
}

