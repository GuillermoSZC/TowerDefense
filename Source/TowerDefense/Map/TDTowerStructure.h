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
class TOWERDEFENSE_API ATDTowerStructure : public AActor
{
    GENERATED_BODY()
public:
    ATDTowerStructure();

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        UStaticMeshComponent* towerStructure;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
        float distanceToUI;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
        bool isUIActive;

    static UPROPERTY(EditAnywhere)
        UTDTowerShop* uiShopRef;

    UPROPERTY(EditDefaultsOnly)
        TSubclassOf<UTDTowerShop> uiShopClass;

    UPROPERTY(EditAnywhere)
        bool isTowerSpawned;

protected:


private:
    static FName StaticMeshName;

    UPROPERTY()
        float distSquared;

    UPROPERTY(EditDefaultsOnly)
        TMap<TEnumAsByte<ETowers>, TSubclassOf<ATDTower>> towerMap;

public:
    virtual void Tick(float DeltaTime) override;

    UFUNCTION(BlueprintCallable)
        void TDTowerSpawn(ETowers _tower);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
        void TDHideUI();

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
        void TDVisibleUI();

protected:
    virtual void BeginPlay() override;

    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
        void TDOnClickedStructure(AActor* Target, FKey ButtonPressed);


private:
    UFUNCTION(BlueprintPure)
        float TDCheckDistanceWithPlayer();

    UFUNCTION(BlueprintPure)
        bool TDCheckPlayerInRange();

    UFUNCTION(BlueprintPure)
        bool TDCanShowUI();

    UFUNCTION()
        void TDOnBuyPhaseStart(int _value);


};
