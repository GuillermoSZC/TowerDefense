#include "UI/TDTowerShop.h"
#include "Map/TDTowerStructure.h"
#include "Utilities/TDButton.h"
#include "UMG/Public/Components/Button.h"

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

void UTDTowerShop::TDBalisticSpawn()
{
    if (owner)
    {
        // owner->TDTowerSpawn(ETowers::Balistic);
    }
}

void UTDTowerShop::TDSonicSpawn()
{
    if (owner)
    {
        // owner->TDTowerSpawn(ETowers::Sonic);
    }
}

void UTDTowerShop::TDDeadRaySpawn()
{
    if (owner)
    {
        // owner->TDTowerSpawn(ETowers::DeathRay);
    }
}

void UTDTowerShop::TDMovementSpawn()
{
    if (owner)
    {
        // owner->TDTowerSpawn(ETowers::Speed);
    }
}

void UTDTowerShop::TDAttackSpawn()
{
    if (owner)
    {
        // owner->TDTowerSpawn(ETowers::Attack);
    }
}

void UTDTowerShop::TDCloseUI()
{
    if (owner)
    {
        // owner->TDHideUI();
    }
}
