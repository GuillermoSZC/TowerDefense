// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TDGameplayEventData.generated.h"

/**
 * 
 */
UCLASS(Blueprintable,BlueprintType)
class TOWERDEFENSE_API UTDGameplayEventData : public UObject
{
	GENERATED_BODY()
	
public:

	UTDGameplayEventData();


public:

     UPROPERTY(EditAnywhere, BlueprintReadWrite)

         FVector VectorPosition;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        AActor* ActorReference;

        UPROPERTY(EditAnywhere, BlueprintReadWrite)
        UStaticMeshComponent* StaticMeshReference;


protected:

private:


public:

protected:

private:

};
