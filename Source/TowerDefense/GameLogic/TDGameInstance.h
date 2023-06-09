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


    void Init() override;

public:

    UPROPERTY(EditDefaultsOnly)
        TMap<EElements, UTexture2D*> elementsImage;

    UPROPERTY()
        bool isInfiniteMap;

    
	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UWorld> worldRef;


protected:


private:


public:
	UFUNCTION(BlueprintCallable)
	void TDOpenMap(UObject* _world);

protected:


private:


};
