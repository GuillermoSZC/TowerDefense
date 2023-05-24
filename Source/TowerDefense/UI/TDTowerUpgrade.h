// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TDUserWidget.h"
#include "TDTowerUpgrade.generated.h"

class ATDTower;
class UTDComposedButton;
class UTDBaseButton;

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
        void TDSetElement(EElements _element);

    
    void TDOnVisibilityChange(ESlateVisibility _visible) override;

};

