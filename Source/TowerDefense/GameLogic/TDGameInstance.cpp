#include "TDGameInstance.h"
#include <Kismet/GameplayStatics.h>
#include "TDGameData.h"

UTDGameInstance::UTDGameInstance()
    : isInfiniteMap(false)
{

}

void UTDGameInstance::Init()
{
    Super::Init();
    
    UTDGameData::TDSetGameInstance(this);
    
}

void UTDGameInstance::TDOpenMap(UObject* _world)
{
    UGameplayStatics::OpenLevelBySoftObjectPtr(_world, worldRef, true);
}
