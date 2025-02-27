#pragma once

#include "CoreMinimal.h"
#include "TDCostWidget.h"
#include <GameplayEffect.h>
#include "GameLogic/ElementsEnum.h"
#include "TDBaseUpgrade.generated.h"

class ATDBase;
class UTDComposedButton;
class UTDBaseButton;
class UTDTextWithImage;
class UTDRichTextBlock;
class UImage;

UCLASS()
class TOWERDEFENSE_API UTDBaseUpgrade : public UTDCostWidget
{
    GENERATED_BODY()
public:
    virtual bool Initialize() override;
    virtual void NativePreConstruct() override;
    virtual void NativeConstruct() override;

public:
#pragma region UI_COMPONENTS
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDComposedButton* plasmaUpgrade;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDComposedButton* fireUpgrade;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDComposedButton* iceUpgrade;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDComposedButton* healthUpgrade;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDComposedButton* speedUpgrade;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDComposedButton* damageUpgrade;



     UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDRichTextBlock* actualElementText;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UImage* actualElementImage;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDRichTextBlock* levelspeedText;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDRichTextBlock* actualLevelspeedText;

        UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDRichTextBlock* leveldamageText;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDRichTextBlock* actualLeveldamageText;

        UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDRichTextBlock* levelhealthText;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDRichTextBlock* actualLevelhealthText;



    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDBaseButton* exit;
#pragma endregion

#pragma region RESOURCES
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDTextWithImage* scrap;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDTextWithImage* health;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDTextWithImage* boots;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDTextWithImage* damage;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDTextWithImage* fire;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDTextWithImage* plasma;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDTextWithImage* ice;

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
    // 
    //     UFUNCTION()
    //         void TDLevelUp();

    UFUNCTION()
        void TDSetGameplayEffect(TSubclassOf<UGameplayEffect> _gameplayEffect);

    void TDOnVisibilityChange(ESlateVisibility _visible) override;

    void TDUpdateLevelsAndElement();

};
