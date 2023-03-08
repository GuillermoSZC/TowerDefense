// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TDElementComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOWERDEFENSE_API UTDElementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTDElementComponent();



public:


	

protected:

private:

	UPROPERTY(VisibleAnywhere)
	EElements ownerElement = EElements::None;

	UPROPERTY(VisibleAnywhere)        
		UTDElement* SpawnedElementData;


	UPROPERTY(VisibleAnywhere)        
		UTDElement* TemporalElementData;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	UFUNCTION(BlueprintCallable)
	void TDSetSpawnedElement(UTDElement* _DataAsset);

    UFUNCTION(BlueprintCallable)
    void TDSetTemporalElement(UTDElement* _DataAsset);

    UFUNCTION(BlueprintCallable)
    void TDRemoveTemporalElement();

	UFUNCTION(BlueprintCallable)
	EElements TDGetOwnerElement();

    UFUNCTION(BlueprintCallable)
	UTDElement* TDGetActualDataAsset();



protected:
    // Called when the game starts
    virtual void BeginPlay() override;

private:


};
