// Fill out your copyright notice in the Description page of Project Settings.


#include "TDPlayerController.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "EnhancedInputComponent.h"
#include "TDMacros.h"
#include "TDCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "UMG/Public/Blueprint/WidgetBlueprintLibrary.h"


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
    

    UEnhancedInputComponent* InputEnhanced = Cast<UEnhancedInputComponent>(InputComponent);

    InputEnhanced->BindAction(HitActionInputAction, ETriggerEvent::Triggered, this, &ATDPlayerController::TDHitAction);
    InputEnhanced->BindAction(MoveSideInputAction, ETriggerEvent::Triggered, this, &ATDPlayerController::TDMoveSideAction);
    InputEnhanced->BindAction(MoveForwardInputAction, ETriggerEvent::Triggered, this, &ATDPlayerController::TDMoveForwardAction);







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

void ATDPlayerController::TDOnOpenUI(UWidget* _widgetRef)
{
    UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(this, _widgetRef);

    UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
    if (Subsystem)
    {
        Subsystem->RemoveMappingContext(DefaultMappingContext);

    }

}

void ATDPlayerController::TDOnCloseUI() 
{
    UWidgetBlueprintLibrary::SetInputMode_GameOnly(this);

    UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
    if (Subsystem)
    {
        Subsystem->AddMappingContext(DefaultMappingContext, 0);
    }

}

