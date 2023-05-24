#include "UI/TDTowerShop.h"
#include "Map/TDTowerStructure.h"
#include "UMG/Public/Components/Button.h"
#include "Components/TDWidgetShopComponent.h"
#include "Utilities/TDTextWithImage.h"
#include "Utilities/TDComposedButton.h"
#include "GameLogic/TDBuyStruct.h"
#include "GameLogic/TDCostManager.h"
#include "GameLogic/TDGameData.h"
#include "GameLogic/TDLootEnum.h"
#include "Utilities/TDBaseButton.h"



UTDTowerShop::UTDTowerShop(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    towerMap.Add(ETowers::Balistic, nullptr);
    towerMap.Add(ETowers::Sonic, nullptr);
    towerMap.Add(ETowers::DeathRay, nullptr);
    towerMap.Add(ETowers::Attack, nullptr);
    towerMap.Add(ETowers::Speed, nullptr);
}

bool UTDTowerShop::Initialize()
{
    Super::Initialize();

    return true;
}

void UTDTowerShop::NativePreConstruct()
{
    Super::NativePreConstruct();

}

void UTDTowerShop::NativeConstruct()
{
    Super::NativeConstruct();

    balisticButton->imgButton->OnClicked.AddDynamic(this, &UTDTowerShop::TDBalisticSpawn);
    sonicButton->imgButton->OnClicked.AddDynamic(this, &UTDTowerShop::TDSonicSpawn);
    deadRayButton->imgButton->OnClicked.AddDynamic(this, &UTDTowerShop::TDDeadRaySpawn);
    movementButton->imgButton->OnClicked.AddDynamic(this, &UTDTowerShop::TDMovementSpawn);
    attackButton->imgButton->OnClicked.AddDynamic(this, &UTDTowerShop::TDAttackSpawn);
    exitButton->OnClicked.AddDynamic(this, &UTDTowerShop::TDCloseUI);
}

void UTDTowerShop::TDOnVisibilityChange(ESlateVisibility _visible)
{
    if (_visible == ESlateVisibility::Visible)
    {
        FBuyCost cost = FBuyCost();
        ITDCostInterface::Execute_TDCalcultateCost(owner->GetOwner(),cost, ELootItems::BalisticBP);       

         balisticButton->scrap->TDSetText(UTDGameData::TDConvertIntToFText(cost.scrapCost));
         balisticButton->bps->TDSetText(UTDGameData::TDConvertIntToFText(cost.BPCost));

         ITDCostInterface::Execute_TDCalcultateCost(owner->GetOwner(), cost, ELootItems::SonicBP);

         sonicButton->scrap->TDSetText(UTDGameData::TDConvertIntToFText(cost.scrapCost));
         sonicButton->bps->TDSetText(UTDGameData::TDConvertIntToFText(cost.BPCost));

         ITDCostInterface::Execute_TDCalcultateCost(owner->GetOwner(), cost, ELootItems::SonicBP);
         deadRayButton->scrap->TDSetText(UTDGameData::TDConvertIntToFText(cost.scrapCost));
         deadRayButton->bps->TDSetText(UTDGameData::TDConvertIntToFText(cost.BPCost));

         ITDCostInterface::Execute_TDCalcultateCost(owner->GetOwner(), cost, ELootItems::SonicBP);
         movementButton->scrap->TDSetText(UTDGameData::TDConvertIntToFText(cost.scrapCost));
         movementButton->bps->TDSetText(UTDGameData::TDConvertIntToFText(cost.BPCost));

         ITDCostInterface::Execute_TDCalcultateCost(owner->GetOwner(), cost, ELootItems::SonicBP);
         attackButton->scrap->TDSetText(UTDGameData::TDConvertIntToFText(cost.scrapCost));
         attackButton->bps->TDSetText(UTDGameData::TDConvertIntToFText(cost.BPCost));

    }
}

void UTDTowerShop::TDBalisticSpawn()
{
    TDSpawnLogic(ETowers::Balistic);
}

void UTDTowerShop::TDSonicSpawn()
{
    TDSpawnLogic(ETowers::Sonic);
}

void UTDTowerShop::TDDeadRaySpawn()
{
    TDSpawnLogic(ETowers::DeathRay);
}

void UTDTowerShop::TDMovementSpawn()
{
    TDSpawnLogic(ETowers::Speed);
}

void UTDTowerShop::TDAttackSpawn()
{
    TDSpawnLogic(ETowers::Attack);
}

void UTDTowerShop::TDCloseUI()
{
    if (owner)
    {
        owner->TDHideUI();
    }
}

void UTDTowerShop::TDSpawnLogic(ETowers _tower)
{
    FVector location = owner->GetOwner()->GetActorLocation();
    UWorld* world = GetWorld();

    world->SpawnActor(towerMap[_tower], &location, &FRotator::ZeroRotator);

    TDEndSpawnLogic();
}

void UTDTowerShop::TDEndSpawnLogic()
{
    if (owner)
    {
        owner->TDHideUI();
        owner->GetOwner()->OnClicked.Clear();
    }
}
