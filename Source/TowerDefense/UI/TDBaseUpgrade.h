// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TDBaseUpgrade.generated.h"

class UTDButton;

UCLASS()
class TOWERDEFENSE_API UTDBaseUpgrade : public UUserWidget
{
    GENERATED_BODY()
public:
    virtual bool Initialize() override;
    virtual void NativePreConstruct() override;
    virtual void NativeConstruct() override;

public:
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDButton* plasmaUpgrade;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDButton* fireUpgrade;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDButton* iceUpgrade;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDButton* healthUpgrade;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDButton* speedUpgrade;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDButton* damageUpgrade;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDButton* exit;

protected:


private:


public:


protected:


private:


};
