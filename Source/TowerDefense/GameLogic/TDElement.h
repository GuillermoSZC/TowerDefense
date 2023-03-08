// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ElementsEnum.h"
#include "TDElement.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UTDElement : public UDataAsset
{
	GENERATED_BODY()
	

public:
	UTDElement();

public:

	UPROPERTY(EditDefaultsOnly)
	EElements ownerElement = EElements::None;


	UPROPERTY(EditDefaultsOnly)
	TMap<EElements, float> ElementsMap;


protected:

private:

public:

protected:

private:


};
