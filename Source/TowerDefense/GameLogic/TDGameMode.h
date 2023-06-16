// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TDObjectPooler.h"
#include "ElementsEnum.h"
#include "TDRoundManager.h"
#include "Delegates/DelegateCombinations.h"
#include "TDLootEnum.h"
#include "GameplayTagContainer.h"
#include "TDGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FLootDropSignature, ELootItems, _item, FGameplayTag, _category, int32, _amount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOndGameOverSignature);


class ATDEnemy;
class UDataTable;
class UTDElement;
class UTDWeightManager;
class UTDGameplayEventData;
class UTDCostWidget;
class UTDTowerShop;
class UTDTowerUpgrade;
class UTDBaseUpgrade;
class ATDCostManager;
class UTDGameOver;

/**
 *
 */
UCLASS()
class TOWERDEFENSE_API ATDGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:

    ATDGameMode();



public:

    UPROPERTY(EditDefaultsOnly, Category = "Classes")
        TSubclassOf<ATDObjectPooler> objectPoolerClass;

    UPROPERTY(EditDefaultsOnly, Category = "Classes")
        TSubclassOf<ATDRoundManager> RoundManagerClass;

    UPROPERTY(EditDefaultsOnly, Category = "Classes")
        TSubclassOf<ATDEnemy> EnemyClass;


    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Classes")
        UDataTable* statsDatatable;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
        TMap<EElements, UTDElement*> elementsDataAssets;


    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
        TMap<EElements, UDataTable*> elementsDataLoot;

    UPROPERTY(EditDefaultsOnly, Category = "Classes")
        TSubclassOf<UTDTowerShop> towerShopClass;

    UPROPERTY(EditDefaultsOnly, Category = "Classes")
        TSubclassOf<UTDTowerUpgrade> towerUpgradeClass;

    UPROPERTY(EditDefaultsOnly, Category = "Classes")
        TSubclassOf<UTDBaseUpgrade> baseUpgradeClass;

    UPROPERTY(EditDefaultsOnly, Category = "Classes")
        TSubclassOf<ATDCostManager> CostManagerClass;

    UPROPERTY(EditDefaultsOnly, Category = "Classes")
        TSubclassOf<UTDGameOver> gameOverClass;

    UPROPERTY(BlueprintAssignable, BlueprintReadWrite, BlueprintCallable)
        FLootDropSignature FLootDropDelegate;

    UPROPERTY()
    FOndGameOverSignature FOndGameOverDelegate;

protected:
    UPROPERTY()
        UTDGameOver* gameOverRef;

private:

    UPROPERTY(Transient)
        UTDGameplayEventData* AbilityStruct;

    UPROPERTY(Transient)
        ATDRoundManager* RoundManagerRef = nullptr;

    UPROPERTY(Transient)
        ATDObjectPooler* ObjectPoolerRef = nullptr;

    UPROPERTY(Transient)
        UTDWeightManager* weightManagerRef = nullptr;

    UPROPERTY()
        TMap<TSubclassOf<UTDCostWidget>, UTDCostWidget*> widgetMap;

    UPROPERTY(Transient)
        ATDCostManager* CostManagerRef = nullptr;




public:

    UTDElement* TDGetDataAssetFromElement(EElements _keyElement);

    UDataTable* TDGetDataLootFromElement(EElements _keyElement);

    UTDCostWidget* TDGetWidgetFromClass(TSubclassOf<UTDCostWidget> _class);

    UFUNCTION(BlueprintCallable)
        void TDGameOver();

    UFUNCTION(BlueprintImplementableEvent)
        void TDOnEndFadeIn();

protected:
    void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

    void StartPlay() override;

    void StartToLeaveMap() override;


    void Reset() override;


private:
    UFUNCTION()
        UTDCostWidget* TDAddToViewport(TSubclassOf<UTDCostWidget> _widgetClass);


};
