// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "UMG/Public/Components/Image.h"
#include "ElementsEnum.h"
#include "TDGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UTDGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UTDGameInstance();
	
public:

	UPROPERTY(EditDefaultsOnly)
	TMap<EElements, UTexture2D*> elementsImage;


protected:


private:


public:


protected:


private:


};
