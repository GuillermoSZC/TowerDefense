// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TDSpawner.generated.h"

class ATDEnemy;
class ATDPathPoint;

UCLASS()
class TOWERDEFENSE_API ATDSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATDSpawner();

public:

	UPROPERTY(EditAnywhere)
	ATDPathPoint* firstWaypoint;


protected:

private:



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void TDSpawnEnemy(ATDEnemy* _enemyRef);



protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;


private:

};
