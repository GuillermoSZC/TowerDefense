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

    buttonsArray.Add(attackButton);
    buttonsArray.Add(balisticButton);
    buttonsArray.Add(sonicButton);
    buttonsArray.Add(deadRayButton);
    buttonsArray.Add(movementButton);

    Super::NativeConstruct();

    balisticButton->imgButton->OnClicked.AddDynamic(this, &UTDTowerShop::TDBalisticSpawn);
    sonicButton->imgButton->OnClicked.AddDynamic(this, &UTDTowerShop::TDSonicSpawn);
    deadRayButton->imgButton->OnClicked.AddDynamic(this, &UTDTowerShop::TDDeadRaySpawn);
    movementButton->imgButton->OnClicked.AddDynamic(this, &UTDTowerShop::TDMovementSpawn);
    attackButton->imgButton->OnClicked.AddDynamic(this, &UTDTowerShop::TDAttackSpawn);
    exitButton->OnClicked.AddDynamic(this, &UTDTowerShop::TDCloseUI);
}

void UTDTowerShop::TDUpdateCost()
{
    TDUpdateBPCostWithItem(balisticButton, ELootItems::BalisticBP);
    TDUpdateBPCostWithItem(sonicButton, ELootItems::SonicBP);
    TDUpdateBPCostWithItem(deadRayButton, ELootItems::DeathRayBP);
    TDUpdateBPCostWithItem(movementButton, ELootItems::SpeedTowerBP);
    TDUpdateBPCostWithItem(attackButton, ELootItems::AttackTowerBP);


    TDUpdateInventoryToText(scrap, ELootItems::Scrap);
    TDUpdateInventoryToText(bpBalistic, ELootItems::BalisticBP);
    TDUpdateInventoryToText(bpSonic, ELootItems::SonicBP);
    TDUpdateInventoryToText(bpDeadRay, ELootItems::DeathRayBP);
    TDUpdateInventoryToText(bpMovement, ELootItems::SpeedTowerBP);
    TDUpdateInventoryToText(bpDamage, ELootItems::AttackTowerBP);
}

void UTDTowerShop::TDOnVisibilityChange(ESlateVisibility _visible)
{
    if (_visible == ESlateVisibility::Visible)
    {
        FUICostUpdateDelegate.Broadcast();
    }
}

void UTDTowerShop::TDBalisticSpawn()
{
    if (ITDCostInterface::Execute_TDCommitBuyUpgrade(owner->GetOwner(), ELootItems::BalisticBP))
    {
        TDSpawnLogic(ETowers::Balistic);
    }
}

void UTDTowerShop::TDSonicSpawn()
{
    if (ITDCostInterface::Execute_TDCommitBuyUpgrade(owner->GetOwner(), ELootItems::SonicBP))
    {
        TDSpawnLogic(ETowers::Sonic);
    }
}

void UTDTowerShop::TDDeadRaySpawn()
{
    if (ITDCostInterface::Execute_TDCommitBuyUpgrade(owner->GetOwner(), ELootItems::DeathRayBP))
    {
        TDSpawnLogic(ETowers::DeathRay);
    }
}

void UTDTowerShop::TDMovementSpawn()
{
    if (ITDCostInterface::Execute_TDCommitBuyUpgrade(owner->GetOwner(), ELootItems::SpeedTowerBP))
    {
        TDSpawnLogic(ETowers::Speed);
    }
}

void UTDTowerShop::TDAttackSpawn()
{
    if (ITDCostInterface::Execute_TDCommitBuyUpgrade(owner->GetOwner(), ELootItems::AttackTowerBP))
    {
        TDSpawnLogic(ETowers::Attack);
    }
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

