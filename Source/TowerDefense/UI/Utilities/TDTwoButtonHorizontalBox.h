// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/HorizontalBox.h"
#include "TDTwoButtonHorizontalBox.generated.h"

class UTDComposedButton;

UCLASS()
class TOWERDEFENSE_API UTDTwoButtonHorizontalBox : public UHorizontalBox
{
    GENERATED_BODY()
public:

public:
    UPROPERTY(EditDefaultsOnly)
        int childCount = 2;
protected:

private:

public:
    UFUNCTION(BlueprintCallable)
        void TDAddButton(UTDComposedButton* _button);

protected:

private:


};
