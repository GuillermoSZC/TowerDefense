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
    ~ATDObjectPooler();


public:

    UPROPERTY(EditAnywhere)
        TArray<TSubclassOf<ATDEnemy>> enemiesClasses;

    UPROPERTY(EditAnywhere)
    int32 InitialSpawn = 5;


protected:

private:


    static  UPROPERTY(Transient) ATDObjectPooler* OwnerPooler;



    UPROPERTY(Transient)
        TArray<ATDEnemy*> disabledEnemies;

    UPROPERTY(Transient)
        TArray<ATDEnemy*> activeEnemies;


    //     UPROPERTY(Transient)
    //         TArray<ATDEnemy*> activeEnemies;
    // 
    //     UPROPERTY(Transient)
    //         TArray<ATDEnemy*> deactivatedenemies;


public:


    static ATDObjectPooler* TDGetObjectPooler(TSubclassOf<ATDObjectPooler> _classRef);

    static ATDObjectPooler* TDGetObjectPooler();

    ATDEnemy* TDGetEnemyFromPool();

    void TDAddEnemyToPool(ATDEnemy* _enemyRef);


protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    // Called every frame
    virtual void Tick(float DeltaTime) override;

private:






};
