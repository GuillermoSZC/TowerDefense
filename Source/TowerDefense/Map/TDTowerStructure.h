// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameLogic/TDTowerEnum.h"
#include "GameLogic/TDBuyStruct.h"
#include "GameLogic/TDLootEnum.h"
#include "Interfaces/TDCostInterface.h"
#include "TDTowerStructure.generated.h"

class UStaticMeshComponent;
class UTDTowerShop;
class ATDTower;
class UTDWidgetShopComponent;

UCLASS()
class TOWERDEFENSE_API ATDTowerStructure : public AActor , public ITDCostInterface
{
    GENERATED_BODY()
public:
    ATDTowerStructure();



public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        UStaticMeshComponent* towerStructure;


    
    UPROPERTY(EditAnywhere, Category = "User Interface")
    UTDWidgetShopComponent* widgetShopRef;





protected:


private:
    static FName StaticMeshName;


    UPROPERTY(EditDefaultsOnly)
        TMap<ETowers, TSubclassOf<ATDTower>> towerMap;

public:
    virtual void Tick(float DeltaTime) override;

    UFUNCTION(BlueprintCallable)
        void TDTowerSpawn(ETowers _tower);

    void TDCalcultateCostWithLoot_Implementation(FBuyCost& _cost, ELootItems _item) override;

    bool TDCanAffordCostWithLoot_Implementation(FBuyCost& _cost) override;

    bool TDCommitBuyUpgrade_Implementation(ELootItems _item) override;

    void TDTriggerOpenUI() override;


protected:
    virtual void BeginPlay() override;




private:


};
