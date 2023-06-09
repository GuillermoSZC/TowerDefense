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
#include "UI/Utilities/TDBaseButton.h"
#include "UI/TDCostWidget.h"
#include "Components/TDWidgetShopComponent.h"
#include "UI/Utilities/TDPlayerHUD.h"


ATDPlayerController::ATDPlayerController()
{

}

void ATDPlayerController::BeginPlay()
{
    Super::BeginPlay();
    playerPawn = GetPawn<ATDCharacter>();

    FInputModeGameAndUI inputMode;
    inputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
    inputMode.SetHideCursorDuringCapture(true);
    SetInputMode(inputMode);

    UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
    if (Subsystem)
    {

        Subsystem->ClearAllMappings();
        Subsystem->AddMappingContext(BuyPhaseMappingContext, 0);

    }

    UTDGameData::TDGetRoundManager()->FOnBuyPhaseStartDelegate.AddDynamic(this, &ATDPlayerController::TDOnBuyPhaseStart);
    UTDGameData::TDGetRoundManager()->FOnCombatPhaseStartDelegate.AddDynamic(this, &ATDPlayerController::TDOnCombatPhaseStart);

    UEnhancedInputComponent* InputEnhanced = Cast<UEnhancedInputComponent>(InputComponent);

    InputEnhanced->BindAction(HitActionInputAction, ETriggerEvent::Triggered, this, &ATDPlayerController::TDHitAction);
    InputEnhanced->BindAction(MoveSideInputAction, ETriggerEvent::Triggered, this, &ATDPlayerController::TDMoveSideAction);
    InputEnhanced->BindAction(MoveForwardInputAction, ETriggerEvent::Triggered, this, &ATDPlayerController::TDMoveForwardAction);
    InputEnhanced->BindAction(PauseInputAction, ETriggerEvent::Triggered, this, &ATDPlayerController::TDChangePauseMenuVisibility);
    InputEnhanced->BindAction(TraceInputAction, ETriggerEvent::Completed, this, &ATDPlayerController::TDTraceFromCameraToOpenUI);

    if (pauseMenuClass)
    {
        pauseMenuRef = CreateWidget<UTDPauseMenu>(this, pauseMenuClass);

        if (pauseMenuRef)
        {
            pauseMenuRef->AddToViewport(1);
            pauseMenuRef->SetVisibility(ESlateVisibility::Collapsed);
            pauseMenuRef->closeButton->OnClicked.AddDynamic(this, &ATDPlayerController::TDClosePauseMenu);
        }
    }

    if (playerHUDClass)
    {
        playerHUDRef = CreateWidget<UTDPlayerHUD>(this, playerHUDClass);

        if (playerHUDRef)
        {
            playerHUDRef->AddToViewport(0);

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

void ATDPlayerController::TDChangePauseMenuVisibility(const FInputActionValue& _value)
{
    if (costWidgetRef)
    {
        costWidgetRef->TDGetOwner()->TDHideUI();
        return;
    }

    if (pauseMenuRef->GetVisibility() == ESlateVisibility::Collapsed)
    {
        TDPauseMenuLogic(ESlateVisibility::Visible, true);
    }
    else
    {
        TDPauseMenuLogic(ESlateVisibility::Collapsed, false);
    }
}

void ATDPlayerController::TDClosePauseMenu()
{
    TDPauseMenuLogic(ESlateVisibility::Collapsed, false);
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
            //TDChangeNotToAvalibleTrace();
            if (playerHUDRef)
            {
                playerHUDRef->SetVisibility(ESlateVisibility::Collapsed);

            }
        }
        else
        {
            FInputModeGameOnly inputMode;
            SetInputMode(inputMode);
            if (playerHUDRef)
            {
                playerHUDRef->SetVisibility(ESlateVisibility::HitTestInvisible);

            }

            UTDGameData::TDGetRoundManager()->TDGetActualPhase() == GamePhase::BuyPhase ? TDOnBuyPhaseStart(0) : TDOnCombatPhaseStart(0);
        }

        pauseMenuRef->SetVisibility(_visibility);
    }
}


void ATDPlayerController::TDChangeToAvalibleTrace()
{
    UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
    if (Subsystem)
    {
        Subsystem->RemoveMappingContext(CombatPhaseMappingContext);
        Subsystem->AddMappingContext(BuyPhaseMappingContext, 0);
    }

}

void ATDPlayerController::TDChangeNotToAvalibleTrace()
{
    UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
    if (Subsystem)
    {
        Subsystem->RemoveMappingContext(BuyPhaseMappingContext);
        Subsystem->AddMappingContext(CombatPhaseMappingContext, 0);

    }
}

void ATDPlayerController::TDOnBuyPhaseStart(int32 _num)
{
    bShowMouseCursor = true;

    TDChangeToAvalibleTrace();
}



void ATDPlayerController::TDOnCombatPhaseStart(int32 _num)
{
    bShowMouseCursor = false;

    TDChangeNotToAvalibleTrace();
}

void ATDPlayerController::TDTraceFromCameraToOpenUI(const FInputActionValue& _value)
{
    FVector screenPos = FVector();
    FVector screenDirection = FVector();
    DeprojectMousePositionToWorld(screenPos, screenDirection);

    FVector endPos = screenPos + (screenDirection * lenghtTrace);

    FHitResult hitresult = FHitResult();

    if (GetWorld()->LineTraceSingleByChannel(hitresult, screenPos, endPos, traceChannel))
    {
        ITDCostInterface* interace = Cast<ITDCostInterface>(hitresult.GetActor());
        interace->TDTriggerOpenUI();
        UKismetSystemLibrary::DrawDebugLine(GetWorld(), screenPos, endPos, FColor::Green, 2.f, 5.f);
    }
    else
    {
        UKismetSystemLibrary::DrawDebugLine(GetWorld(), screenPos, endPos, FColor::Red, 2.f, 5.f);
    }
}

void ATDPlayerController::TDOnOpenUI(UTDCostWidget* _widgetRef)
{
    costWidgetRef = _widgetRef;

    TDChangeNotToAvalibleTrace();

    SetIgnoreMoveInput(true);
    SetIgnoreLookInput(true);
}

void ATDPlayerController::TDOnCloseUI()
{
    costWidgetRef = nullptr;

    SetIgnoreMoveInput(false);
    SetIgnoreLookInput(false);
   

    UTDGameData::TDGetRoundManager()->TDGetActualPhase() == GamePhase::BuyPhase ? TDChangeToAvalibleTrace() : TDChangeNotToAvalibleTrace();

}

UTDPlayerHUD* ATDPlayerController::TDGetPLayerHUD()
{
    return playerHUDRef;
}
