// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TDDeclareDelegates.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangeSignature, float, _newValue);






UCLASS()
class TOWERDEFENSE_API UTDDeclareDelegates : public UObject
{
	GENERATED_BODY()
	
};
