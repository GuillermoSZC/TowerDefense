// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ElementsEnum.h"
#include "Delegates/TDDeclareDelegates.h"
#include "TDElementComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TOWERDEFENSE_API UTDElementComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UTDElementComponent();

public:

    UPROPERTY(BlueprintAssignable)
    FOnElementChangeSignature OnElementChangeDelegate;

protected:
private:


    UPROPERTY(VisibleAnywhere)
        EElements ownerElement = EElements::None;

    //DataAsset that store the ownerElement and the damage multipliers to other classes
    UPROPERTY(VisibleAnywhere)
        UTDElement* SpawnedElementData;


    UPROPERTY(VisibleAnywhere)
        UTDElement* TemporalElementData;


public:
    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


    UFUNCTION(BlueprintCallable)
        void TDSetSpawnedElement(EElements _element);
 
    UFUNCTION(BlueprintCallable)
        void TDSetTemporalElement(EElements _element);

    UFUNCTION(BlueprintCallable)
        void TDRemoveTemporalElement();

    UFUNCTION(BlueprintPure)
        EElements TDGetOwnerElement();

    UFUNCTION(BlueprintCallable)
        UTDElement* TDGetActualDataAsset();


    UFUNCTION(BlueprintPure)
        float TDGetDamageMultiplier(EElements _element);

    UFUNCTION(BlueprintPure)
    EElements TDGetSpawnedElement();

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

private:


};
