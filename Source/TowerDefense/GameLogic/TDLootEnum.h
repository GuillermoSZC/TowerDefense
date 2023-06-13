// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"



UENUM(BlueprintType)
enum class ELootItems : uint8
{
    None UMETA(DisplayName = "/",ToolTip = "For category - based drops"),
    Scrap UMETA(ToolTip = "Common Item"),
    SwordBP UMETA(ToolTip = "Rare Item"),
    ArmorBP UMETA(ToolTip = "Rare Item"),
    BootsBP UMETA(ToolTip = "Rare Item"),
    BalisticBP UMETA(ToolTip = "Rare Item"),
    SonicBP UMETA(ToolTip = "Rare Item"),
    DeathRayBP UMETA(ToolTip = "Rare Item"),
    SpeedTowerBP UMETA(ToolTip = "Rare Item"),
    AttackTowerBP UMETA(ToolTip = "Rare Item"),
    Fire UMETA(ToolTip = "Rare Item"),
    Ice UMETA(ToolTip = "Rare Item"),
    Plasma UMETA(ToolTip = "Rare Item"),
    Invalid UMETA(ToolTip = "Invalid"),
};


ENUM_RANGE_BY_COUNT(ELootItems, ELootItems::Invalid)