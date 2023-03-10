// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Utilities/TDTextWithImage.h"
#include "TDRowBase.generated.h"

/**
 *
 */
UCLASS()
class TOWERDEFENSE_API UTDRowBase : public UTDTextWithImage
{
    GENERATED_BODY()

public:
    virtual bool Initialize() override;
    virtual void NativePreConstruct() override;
    virtual void NativeConstruct() override;

public:
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        class UTDText* descriptionText;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        class UTDButton* buyButton;

protected:


private:


public:


protected:


private:


};
