// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TDItemStrcut.generated.h"

/**
 * 
 */



USTRUCT()
struct FTDItemStruct
{
    GENERATED_BODY()

    ELootItems dropLoot;
    FGameplayTag categoryLoot;
    int32 amountLoot;

    FTDItemStruct()
    {
        dropLoot = ELootItems::None;
        categoryLoot = FGameplayTag();
        amountLoot = 0;
    }



    FTDItemStruct(ELootItems _dropLoot, FGameplayTag _tag, int32 _amount = 1)
    {
        dropLoot = _dropLoot;
        categoryLoot = _tag;
        amountLoot = _amount;
    }



};

