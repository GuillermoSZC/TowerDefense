// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TDObjectPooler.generated.h"

UCLASS()
class TOWERDEFENSE_API ATDObjectPooler : public AActor
{
	GENERATED_BODY()
	
private:	

	ATDObjectPooler();


protected:

private:

	static ATDObjectPooler* OwnerPooler;


public:


	static ATDObjectPooler* TDGetObjectPooler();


    // Called every frame
    virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:






};
