#pragma once

#include "CoreMinimal.h"
#include "UI/TDUserWidget.h"
#include "TDPauseMenu.generated.h"

class UTDInventory;
class UWidgetSwitcher;
class UTDBaseButton;
class UTDGraphicSettings;
class UTDSoundSettings;
class UTDInputSettings;
class UTDButton;

UCLASS()
class TOWERDEFENSE_API UTDPauseMenu : public UTDUserWidget
{
    GENERATED_BODY()
public:
    virtual bool Initialize() override;
    virtual void NativePreConstruct() override;
    virtual void NativeConstruct() override;

public:
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UWidgetSwitcher* MainSwitcher;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDInventory* inventory;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDButton* inventoryButton;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDButton* graphicsButton;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDButton* soundButton;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDButton* inputButton;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDBaseButton* closeButton;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDGraphicSettings* graphics;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDSoundSettings* sound;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDInputSettings* input;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDButton* mainMenu;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDButton* exit;

protected:

private:
    static UPROPERTY(Transient)
        UTDPauseMenu* owner;

public:
    UFUNCTION()
        static UTDPauseMenu* TDGetPauseMenuRef();

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
        void TDFadeIn();

    UFUNCTION(BlueprintImplementableEvent)
        void TDGoToMainMenu();

protected:
    UFUNCTION()
        virtual void TDOnVisibilityChange(ESlateVisibility _visible);


private:
    UFUNCTION()
        void TDOnInventory();

    UFUNCTION()
        void TDOnGraphics();

    UFUNCTION()
        void TDOnSound();

    UFUNCTION()
        void TDOnInput();

    UFUNCTION()
        void TDSetWidgetSwitcherIndex(int _value);

    UFUNCTION()
        void TDExitGame();


};
