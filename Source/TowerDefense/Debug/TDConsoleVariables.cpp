// Fill out your copyright notice in the Description page of Project Settings.


#include "Debug/TDConsoleVariables.h"

#define CREATE_BOOL_CONSOLE_VAR_DRAW_DEBUG(VAR_NAME,CLASS_NAME) \
static TAutoConsoleVariable<int32> Cvar##VAR_NAME( \
TEXT("TD.ShowDebug" CLASS_NAME), \
0, \
TEXT("Draws debug info about " CLASS_NAME) \
TEXT("  0: off") \
TEXT("  1: on"), \
ECVF_Cheat);


CREATE_BOOL_CONSOLE_VAR_DRAW_DEBUG(ShowDebugBalisticTower, "BalisticTower");

CREATE_BOOL_CONSOLE_VAR_DRAW_DEBUG(ShowDebugSonicTower, "SonicTower");