#include "UI/Utilities/TDButtonMap.h"
#include <Engine/World.h>
#include <Kismet/GameplayStatics.h>

bool UTDButtonMap::Initialize()
{
    Super::Initialize();

    return true;
}

void UTDButtonMap::NativePreConstruct()
{
    Super::NativePreConstruct();

}

void UTDButtonMap::NativeConstruct()
{
    Super::NativeConstruct();

    if (ownerButton)
    {
        ownerButton->OnClicked.AddDynamic(this, &UTDButtonMap::TDOpenLevel);
    }
}

void UTDButtonMap::TDSetLevelReference(TSoftObjectPtr<UWorld> _levelReference)
{
    levelReference = _levelReference;
}

TSoftObjectPtr<UWorld> UTDButtonMap::TDGetLevelReference() const
{
    return levelReference;
}

void UTDButtonMap::TDOpenLevel()
{
    UGameplayStatics::OpenLevelBySoftObjectPtr(this, levelReference, true);
}
