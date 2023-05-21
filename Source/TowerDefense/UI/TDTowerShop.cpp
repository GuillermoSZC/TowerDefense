#include "UI/TDTowerShop.h"
#include "Map/TDTowerStructure.h"
#include "Utilities/TDButton.h"
#include "UMG/Public/Components/Button.h"
#include "Components/TDWidgetShopComponent.h"
#include "Utilities/TDTextWithImage.h"


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

    balisticButton->ownerButton->OnClicked.AddDynamic(this, &UTDTowerShop::TDBalisticSpawn);
    sonicButton->ownerButton->OnClicked.AddDynamic(this, &UTDTowerShop::TDSonicSpawn);
    deadRayButton->ownerButton->OnClicked.AddDynamic(this, &UTDTowerShop::TDDeadRaySpawn);
    movementButton->ownerButton->OnClicked.AddDynamic(this, &UTDTowerShop::TDMovementSpawn);
    attackButton->ownerButton->OnClicked.AddDynamic(this, &UTDTowerShop::TDAttackSpawn);
    exitButton->ownerButton->OnClicked.AddDynamic(this, &UTDTowerShop::TDCloseUI);
}

void UTDTowerShop::TDOnVisibilityChange(ESlateVisibility _visible)
{
    if (_visible == ESlateVisibility::Visible)
    {
        FBuyCost cost = FBuyCost();
        cost = UTDGameData::TDGetCostManager()->TDCalculateTowerBuyCost(ELootItems::BalisticBP);

        BalisticCostText->TDSetText(UTDGameData::TDConvertIntToFText(cost.scrapCost));
        SonicCostText->TDSetText(UTDGameData::TDConvertIntToFText(cost.BPCost));

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
