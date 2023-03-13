// Fill out your copyright notice in the Description page of Project Settings.


#include "TDCharacter.h"

// Sets default values
ATDCharacter::ATDCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATDCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATDCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATDCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

