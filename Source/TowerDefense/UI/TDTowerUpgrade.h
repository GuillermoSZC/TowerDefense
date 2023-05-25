// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TDUserWidget.h"
#include "TDTowerUpgrade.generated.h"

class ATDTower;
class UTDComposedButton;
class UTDBaseButton;
class UTDTextWithImage;

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
        UTDComposedButton* plasmaUpgrade;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDComposedButton* fireUpgrade;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDComposedButton* iceUpgrade;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDComposedButton* levelUp;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDBaseButton* exit;

#pragma region RESOURCES
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDTextWithImage* scrap;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDTextWithImage* blueprint;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDTextWithImage* fire;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDTextWithImage* plasma;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDTextWithImage* ice;
#pragma endregion

protected:


private:


public:

protected:
    void TDUpdateCost() override;

private:
#pragma region BUTTONS_IMPLEMENTATION
    UFUNCTION()
        void TDPlasmaUpgrade();

    UFUNCTION()
        void TDFireUpgrade();

    UFUNCTION()
        void TDIceUpgrade();

    UFUNCTION()
        void TDCloseUI();
#pragma endregion

    UFUNCTION()
        void TDLevelUp();

    UFUNCTION()
        void TDBuyElement(EElements _element);


    void TDOnVisibilityChange(ESlateVisibility _visible) override;



};

