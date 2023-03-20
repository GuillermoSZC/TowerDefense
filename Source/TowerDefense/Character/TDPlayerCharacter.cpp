// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TDPlayerCharacter.h"

ATDPlayerCharacter::ATDPlayerCharacter()
{

}

void ATDPlayerCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);


}

void ATDPlayerCharacter::BeginPlay()
{
    Super::BeginPlay();

    TDActivateDelegates();
}
