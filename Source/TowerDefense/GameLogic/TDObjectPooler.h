// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TDObjectPooler.generated.h"

class ATDEnemy;

UCLASS()
class TOWERDEFENSE_API ATDObjectPooler : public AActor
{
    GENERATED_BODY()

private:

    ATDObjectPooler();


public:

    UPROPERTY(EditAnywhere)
        TArray<TSubclassOf<ATDEnemy>> enemiesClasses;


protected:

private:

   
        static  UPROPERTY(Transient) ATDObjectPooler* OwnerPooler;



//     UPROPERTY(Transient)
//         TArray<ATDEnemy*> activeEnemies;
// 
//     UPROPERTY(Transient)
//         TArray<ATDEnemy*> deactivatedenemies;


public:


    static ATDObjectPooler* TDGetObjectPooler(TSubclassOf<ATDObjectPooler> _classRef);




protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    // Called every frame
    virtual void Tick(float DeltaTime) override;

private:






};
