// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TDBuyStruct.generated.h"


USTRUCT(BlueprintType)
struct FBuyCost
{
    GENERATED_BODY()


        UPROPERTY(EditAnywhere,BlueprintReadWrite)
        int32 scrapCost;
        UPROPERTY(EditAnywhere,BlueprintReadWrite)
        int32 BPCost;
        UPROPERTY(EditAnywhere,BlueprintReadWrite)
        int32 GemCost;



};