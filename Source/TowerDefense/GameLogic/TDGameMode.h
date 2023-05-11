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

    UPROPERTY(EditDefaultsOnly)
        TSubclassOf<ATDObjectPooler> objectPoolerClass;

    UPROPERTY(EditDefaultsOnly)
        TSubclassOf<ATDRoundManager> RoundManagerClass;

    UPROPERTY(EditDefaultsOnly)
        TSubclassOf<ATDEnemy> EnemyClass;


    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
        UDataTable* statsDatatable;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
        TMap<EElements, UTDElement*> elementsDataAssets;

    UPROPERTY()
        TSubclassOf<UTDTowerShop> towerShopClass;

    UPROPERTY()
        TSubclassOf<UTDTowerUpgrade> towerUpgradeClass;

    UPROPERTY()
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

//     UPROPERTY()
//         TMap<TSubclassOf<UTDUserWidget>, UTDUserWidget*> widgetMap;



public:

    UTDElement* TDGetDataAssetFromElement(EElements _keyElement);

protected:
    void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

    void StartPlay() override;

    void StartToLeaveMap() override;


    void Reset() override;


private:
//     UFUNCTION()
//         void TDAddToViewport(UTDUserWidget* _widget, TSubclassOf<UTDUserWidget> _widgetClass);


};
