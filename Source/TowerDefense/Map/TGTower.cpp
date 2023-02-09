// Fill out your copyright notice in the Description page of Project Settings.

#include "TGTower.h"

// Sets default values
ATGTower::ATGTower()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATGTower::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATGTower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

 int ATGTower::TGGApplyEffect_Implementation() 
{
	return 0;
}

