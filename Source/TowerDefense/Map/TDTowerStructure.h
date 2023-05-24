// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameLogic/TDTowerEnum.h"
#include "TDTowerStructure.generated.h"

class UStaticMeshComponent;
class UTDTowerShop;
class ATDTower;

UCLASS()
class TOWERDEFENSE_API ATDTowerStructure : public AActor , public ITDCostInterface
{
    GENERATED_BODY()
public:
    ATDTowerStructure();


   

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        UStaticMeshComponent* towerStructure;

protected:


private:
    static FName StaticMeshName;


    UPROPERTY(EditDefaultsOnly)
        TMap<TEnumAsByte<ETowers>, TSubclassOf<ATDTower>> towerMap;

public:
    virtual void Tick(float DeltaTime) override;

    UFUNCTION(BlueprintCallable)
        void TDTowerSpawn(ETowers _tower);

    void TDCalcultateCost_Implementation(FBuyCost& _cost, ELootItems _item) override;

protected:
    virtual void BeginPlay() override;




private:


};
