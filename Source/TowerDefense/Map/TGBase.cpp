// Fill out your copyright notice in the Description page of Project Settings.


#include "TGBase.h"

// Sets default values
ATGBase::ATGBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATGBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATGBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

