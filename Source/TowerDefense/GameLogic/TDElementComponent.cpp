// Fill out your copyright notice in the Description page of Project Settings.


#include "GameLogic/TDElementComponent.h"
#include "TDElement.h"
#include "TDGameData.h"
#include "TDGameMode.h"


UTDElementComponent::UTDElementComponent()
{

    PrimaryComponentTick.bCanEverTick = false;


}


void UTDElementComponent::BeginPlay()
{
    Super::BeginPlay();
}


// Called every frame
void UTDElementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UTDElementComponent::TDSetSpawnedElement(EElements _element)
{
    SpawnedElementData = UTDGameData::TDGetGameMode()->TDGetDataAssetFromElement(_element);
    ownerElement = SpawnedElementData->ownerElement;
    OnElementChangeDelegate.Broadcast(ownerElement);
}

void UTDElementComponent::TDSetTemporalElement(EElements _element)
{
    TemporalElementData = UTDGameData::TDGetGameMode()->TDGetDataAssetFromElement(_element);
    ownerElement = TemporalElementData->ownerElement;
    OnElementChangeDelegate.Broadcast(ownerElement);
}

void UTDElementComponent::TDRemoveTemporalElement()
{
    TemporalElementData = nullptr;
    ownerElement = SpawnedElementData->ownerElement;
    OnElementChangeDelegate.Broadcast(ownerElement);
}

EElements UTDElementComponent::TDGetOwnerElement()
{
    return ownerElement;
}

UTDElement* UTDElementComponent::TDGetActualDataAsset()
{
    if (TemporalElementData)
    {
        return TemporalElementData;
    }

    return SpawnedElementData;
}

float UTDElementComponent::TDGetDamageMultiplier(EElements _element)
{
    UTDElement* tempRef = SpawnedElementData;

    if (TemporalElementData)
    {
        tempRef = TemporalElementData;
    }

    return tempRef->ElementsMap[_element];

}

