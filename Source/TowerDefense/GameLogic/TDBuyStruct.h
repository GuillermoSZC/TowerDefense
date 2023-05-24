// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TDLootEnum.h"
#include "TDBuyStruct.generated.h"


USTRUCT(BlueprintType)
struct FBuyCost
{
    GENERATED_BODY()


        UPROPERTY(EditAnywhere, BlueprintReadWrite)
        int32 scrapCost;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        ELootItems BPItem;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        int32 BPCost;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        ELootItems GemItem;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        int32 GemCost;

    FBuyCost()
    {
        scrapCost = 0;
        BPCost = 0;
        GemCost = 0;
        BPItem = ELootItems::None;
        GemItem = ELootItems::None;
    }


};