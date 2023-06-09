#include "UI/Utilities/TDButtonMap.h"
#include <Engine/World.h>
#include <Kismet/GameplayStatics.h>
#include "GameLogic/TDGameData.h"
#include "GameLogic/TDGameInstance.h"

bool UTDButtonMap::Initialize()
{
    Super::Initialize();

    if (ownerButton)
    {
        ownerButton->OnClicked.AddDynamic(this, &UTDButtonMap::TDOpenLevel);
    }

    return true;
}

void UTDButtonMap::NativePreConstruct()
{
    Super::NativePreConstruct();
}

void UTDButtonMap::NativeConstruct()
{
    Super::NativeConstruct();   
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
    UTDGameData::TDGetGameInstance()->isInfiniteMap = isInfinite;
    UGameplayStatics::OpenLevelBySoftObjectPtr(this, levelReference, true);
}

bool UTDButtonMap::TDGetIsInfinite() const
{
    return isInfinite;
}

void UTDButtonMap::TDSetIsInfinite(bool _value)
{
    isInfinite = _value;
}
