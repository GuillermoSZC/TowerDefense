// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TDTowerStructure.generated.h"

class UStaticMeshComponent;
class UTDTowerShop;

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

protected:


private:
    static FName StaticMeshName;

    UPROPERTY()
        float distSquared;

public:
    virtual void Tick(float DeltaTime) override;

protected:
    virtual void BeginPlay() override;

    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
        void TDOnClickedStructure(AActor* Target, FKey ButtonPressed);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
        void TDHideUI();

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
        void TDVisibleUI();

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
