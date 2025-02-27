// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TDPlayerHUD.generated.h"



/**
 *
 */
UCLASS()
class TOWERDEFENSE_API UTDPlayerHUD : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual bool Initialize() override;
    virtual void NativePreConstruct() override;
    virtual void NativeConstruct() override;
    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        class UTDText* roundText;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        class UTDText* roundNum;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        class UTDText* enemyText;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        class UTDText* enemyCounter;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        class UImage* firstElement;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        class UImage* secondElement;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        class UImage* thirdElement;


      UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        class UTDLogWidget* LogWidget;

    UPROPERTY()
        TArray<UImage*> elementsArray;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        class UTDText* timer;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        class UTDText* phase;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        class UImage* playerElement;

            UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        class UImage* healthBarContainer;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        class UTDHealthBar* healthBar;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        class UTDText* healthNumber;


    




protected:




private:
    UPROPERTY(Transient)
        class ATDRoundManager* roundManager;





public:


    UFUNCTION(BlueprintCallable)
        void TDInitialize();

    UFUNCTION()
        void TDVisibilityToShopUIs(ESlateVisibility _visibility);


    UFUNCTION()
    void TDPlayerGameOver();


protected:


private:
    UFUNCTION()
        void TDSetCombatUI(int32 _value);

    UFUNCTION()
        void TDSetBuyUI(int32 _value);

    UFUNCTION()
        void TDSetElementsUI(TArray<EElements>& _elements);

    UFUNCTION()
        void TDSetElementsVisibility(ESlateVisibility _visibility);

    UFUNCTION()
        void TDSetPlayerElement(EElements _element);

    UFUNCTION()
        void TDSetEnemyCounter(int32 _counter);

    UFUNCTION()
        void TDUpdateHealthNumber(float _percentage, float _actualHp);



};
