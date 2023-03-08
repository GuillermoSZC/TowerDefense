// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TDRoundElementsType.generated.h"

/**
 * 
 */
UCLASS(editinlinenew, DefaultToInstanced, BlueprintType, Blueprintable)
class TOWERDEFENSE_API UTDRoundElementsType : public UObject
{
	GENERATED_BODY()
	
public:

	UTDRoundElementsType();

public:
	UPROPERTY(EditAnywhere)
	TArray<EElements> GrantedElements;

	UPROPERTY(EditAnywhere)
	int8 numberOfRandomElements;


    UPROPERTY(VisibleAnywhere)
        TArray<EElements> RandomElements;

protected:


private:


public:
	UFUNCTION()
	TArray<EElements> TDGetRoundElements(TArray<EElements>& _elementsArray);

protected:

private:



};
