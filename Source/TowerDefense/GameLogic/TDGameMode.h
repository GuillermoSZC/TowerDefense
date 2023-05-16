// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TDObjectPooler.h"
#include "ElementsEnum.h"
#include "TDRoundManager.h"

#include "TDGameMode.generated.h"

class ATDEnemy;
class UDataTable;
class UTDElement;
class UTDWeightManager;
class UTDGameplayEventData;
class UTDUserWidget;
class UTDTowerShop;
class UTDTowerUpgrade;
class UTDBaseUpgrade;

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

protected:


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
         TMap<TSubclassOf<UTDUserWidget>, UTDUserWidget*> widgetMap;
     
   



public:

    UTDElement* TDGetDataAssetFromElement(EElements _keyElement);

    UDataTable* TDGetDataLootFromElement(EElements _keyElement);

    UTDUserWidget* TDGetWidgetFromClass(TSubclassOf<UTDUserWidget> _class);

protected:
    void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

    void StartPlay() override;

    void StartToLeaveMap() override;


    void Reset() override;


private:
     UFUNCTION()
         UTDUserWidget* TDAddToViewport(TSubclassOf<UTDUserWidget> _widgetClass);


};
