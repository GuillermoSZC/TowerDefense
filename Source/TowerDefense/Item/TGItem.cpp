// Fill out your copyright notice in the Description page of Project Settings.


#include "TGItem.h"

// Sets default values
ATGItem::ATGItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATGItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATGItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

