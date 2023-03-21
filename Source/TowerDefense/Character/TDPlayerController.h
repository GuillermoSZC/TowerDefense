// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "TDPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class ATDCharacter;

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

protected:



private:

    UPROPERTY(Transient)
    ATDCharacter* playerPawn;

public:

protected:



    virtual void BeginPlay() override;


private:


    void TDMoveForwardAction(const FInputActionValue& _value);
    void TDMoveSideAction(const FInputActionValue& _value);
    void TDHitAction(const FInputActionValue& _value);

};
