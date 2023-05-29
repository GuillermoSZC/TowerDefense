// Fill out your copyright notice in the Description page of Project Settings.


#include "TDGameMode.h"
#include "TDGameData.h"
#include "TDObjectPooler.h"
#include "Gas/TDGameplayEventData.h"
#include "TDWeightManager.h"
#include "Engine/DataTable.h"
#include "TDElement.h"
#include "UI/TDTowerShop.h"
#include "UI/TDTowerUpgrade.h"
#include "UI/TDBaseUpgrade.h"
#include "TDGameInstance.h"
#include "TDCostManager.h"


ATDGameMode::ATDGameMode()
{
    UTDGameData::TDResetGameData();

    elementsDataAssets.Empty();

    elementsDataAssets.Add(EElements::None, nullptr);
    elementsDataAssets.Add(EElements::Fire, nullptr);
    elementsDataAssets.Add(EElements::Freeze, nullptr);
    elementsDataAssets.Add(EElements::Plasma, nullptr);


    elementsDataLoot.Add(EElements::None, nullptr);
    elementsDataLoot.Add(EElements::Fire, nullptr);
    elementsDataLoot.Add(EElements::Freeze, nullptr);
    elementsDataLoot.Add(EElements::Plasma, nullptr);
}


void ATDGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{

    Super::InitGame(MapName, Options, ErrorMessage);

    UTDGameData::TDSetGameMode(this);

    UTDGameInstance* gameInstanceRef = Cast<UTDGameInstance>(GetGameInstance());
    UTDGameData::TDSetGameInstance(gameInstanceRef);


    UWorld* world = GetWorld();
    UTDGameData::TDSetWorld(world);

    AbilityStruct = NewObject<UTDGameplayEventData>(UTDGameplayEventData::StaticClass());
    UTDGameData::TDSetAbilityStruct(AbilityStruct);


    ObjectPoolerRef = world->SpawnActor<ATDObjectPooler>(objectPoolerClass);
    UTDGameData::TDSetObjectPooler(ObjectPoolerRef);


    RoundManagerRef = world->SpawnActor<ATDRoundManager>(RoundManagerClass);
    UTDGameData::TDSetRoundManager(RoundManagerRef);

    weightManagerRef = NewObject<UTDWeightManager>(UTDWeightManager::StaticClass(), FName(TEXT("WeightManager")), EObjectFlags::RF_MarkAsRootSet);
    UTDGameData::TDSetWeightManager(weightManagerRef);
    weightManagerRef->TDSetDataTable(statsDatatable);


    CostManagerRef = world->SpawnActor<ATDCostManager>(CostManagerClass);
    UTDGameData::TDSetCostManager(CostManagerRef);


    UTDCostWidget* uiTowerShop = TDAddToViewport(towerShopClass);
    UTDCostWidget* uiTowerUpgrade = TDAddToViewport(towerUpgradeClass);
    UTDCostWidget* uiBaseUpgrade = TDAddToViewport(baseUpgradeClass);

    widgetMap.Add(towerShopClass, uiTowerShop);
    widgetMap.Add(towerUpgradeClass, uiTowerUpgrade);
    widgetMap.Add(baseUpgradeClass, uiBaseUpgrade);
}


UTDElement* ATDGameMode::TDGetDataAssetFromElement(EElements _keyElement)
{
    return elementsDataAssets[_keyElement];
}

UDataTable* ATDGameMode::TDGetDataLootFromElement(EElements _keyElement)
{
    return elementsDataLoot[_keyElement];
}

UTDCostWidget* ATDGameMode::TDGetWidgetFromClass(TSubclassOf<UTDCostWidget> _class)
{
    return widgetMap[_class];
}

void ATDGameMode::StartPlay()
{
    Super::StartPlay();


    RoundManagerRef->TDPostBeginPlay();
}

void ATDGameMode::StartToLeaveMap()
{
    Super::StartToLeaveMap();

    UTDGameData::TDResetGameData();
}

void ATDGameMode::Reset()
{
    Super::Reset();
    widgetMap.Empty();
}

UTDCostWidget* ATDGameMode::TDAddToViewport(TSubclassOf<UTDCostWidget> _widgetClass)
{
    UTDCostWidget* _widget = nullptr;
    _widget = CreateWidget<UTDCostWidget>(GetWorld(), _widgetClass);
    _widget->AddToViewport();
    _widget->SetVisibility(ESlateVisibility::Collapsed);
    return _widget;
}
