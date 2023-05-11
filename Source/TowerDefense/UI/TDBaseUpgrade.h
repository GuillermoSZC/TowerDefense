// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TDUserWidget.h"
#include "TDBaseUpgrade.generated.h"

class UTDButton;
class ATDBase;

UCLASS()
class TOWERDEFENSE_API UTDBaseUpgrade : public UTDUserWidget
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
#pragma region BUTTONS_IMPLEMENTATION
    UFUNCTION()
        void TDPlasmaUpgrade();

    UFUNCTION()
        void TDFireUpgrade();

    UFUNCTION()
        void TDIceUpgrade();

    UFUNCTION()
        void TDHealthUpgrade();

    UFUNCTION()
        void TDSpeedUpgrade();

    UFUNCTION()
        void TDDamageUpgrade();

    UFUNCTION()
        void TDCloseUI();

#pragma endregion
};
