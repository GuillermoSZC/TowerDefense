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

void UTDElementComponent::TDSetTemporalElement(AActor* _instigator,EElements _element)
{
    TemporalElementData = UTDGameData::TDGetGameMode()->TDGetDataAssetFromElement(_element);
    ownerElement = TemporalElementData->ownerElement;
    heapTemporalElements.Add(_instigator, _element);
    OnElementChangeDelegate.Broadcast(ownerElement);


}

void UTDElementComponent::TDRemoveTemporalElement(AActor* _instigator)
{
    heapTemporalElements.Remove(_instigator);

    if (heapTemporalElements.IsEmpty())
    {
        TemporalElementData = nullptr;
        ownerElement = SpawnedElementData->ownerElement;
        OnElementChangeDelegate.Broadcast(ownerElement);
    }
    else
    {
        TArray<AActor*>  keys;
        heapTemporalElements.GetKeys(keys);
        EElements NextHeapElement = heapTemporalElements[keys[0]];        
        TemporalElementData = UTDGameData::TDGetGameMode()->TDGetDataAssetFromElement(NextHeapElement);
        ownerElement = TemporalElementData->ownerElement;
        OnElementChangeDelegate.Broadcast(ownerElement);

    }

   
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

EElements UTDElementComponent::TDGetSpawnedElement()
{
    return SpawnedElementData->ownerElement;
}

