#pragma once

#include "CoreMinimal.h"
#include "UI/TDUserWidget.h"
#include "TDMainMenu.generated.h"

class UTDButton;
class UTDLevelSelector;
class UWidgetSwitcher;

UCLASS()
class TOWERDEFENSE_API UTDMainMenu : public UTDUserWidget
{
    GENERATED_BODY()

public:
    virtual bool Initialize() override;
    virtual void NativePreConstruct() override;
    virtual void NativeConstruct() override;

public:
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDButton* normalMode;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDButton* infiniteMode;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDButton* graphics;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDButton* sound;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDButton* input;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDButton* exit;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UWidgetSwitcher* mainMenuSwitcher;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDLevelSelector* levelsSelector;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDLevelSelector* infiniteLevelsSelector;

protected:


private:


public:
    UFUNCTION()
        void TDLevelsSelector();

    UFUNCTION()
        void TDInfiniteLevelsSelector();

    UFUNCTION()
        void TDGraphics();

    UFUNCTION()
        void TDSound();

    UFUNCTION()
        void TDInput();

    UFUNCTION()
        void TDExit();

protected:


private:


};
