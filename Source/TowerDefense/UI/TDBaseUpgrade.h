// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TDUserWidget.h"
#include <GameplayEffect.h>
#include "GameLogic/ElementsEnum.h"
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
#pragma region UI_COMPONENTS
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
#pragma endregion

    UPROPERTY(EditDefaultsOnly)
        TSubclassOf<UGameplayEffect> healthEffect;

    UPROPERTY(EditDefaultsOnly)
        TSubclassOf<UGameplayEffect> speedEffect;

    UPROPERTY(EditDefaultsOnly)
        TSubclassOf<UGameplayEffect> damageEffect;

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

    UFUNCTION()
        void TDSetElement(EElements _element);

    UFUNCTION()
        void TDLevelUp();

    UFUNCTION()
        void TDSetGameplayEffect(TSubclassOf<UGameplayEffect> _gameplayEffect);
};
