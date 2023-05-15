// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TDUserWidget.h"
#include "TDTowerUpgrade.generated.h"

class UTDButton;
class ATDTower;

UCLASS()
class TOWERDEFENSE_API UTDTowerUpgrade : public UTDUserWidget
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
        UTDButton* levelUp;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDButton* exit;

protected:


private:


public:

protected:


private:
#pragma region BUTTONS_IMPLEMENTATION
    UFUNCTION()
        void TDPlasmaUpgrade();

    UFUNCTION()
        void TDFireUpgrade();

    UFUNCTION()
        void TDIceUpgrade();

    UFUNCTION()
        void TDLevelUp();

    UFUNCTION()
        void TDCloseUI();

    UFUNCTION()
        void TDSetElement(EElements _element);
#pragma endregion
};
