// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TDRow.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UTDRow : public UUserWidget
{
	GENERATED_BODY()

public:
    virtual bool Initialize() override;
    virtual void NativePreConstruct() override;
    virtual void NativeConstruct() override;
};
