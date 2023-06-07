#pragma once

#include "CoreMinimal.h"
#include "UI/TDUserWidget.h"
#include "TDMainMenu.generated.h"

class UTDButton;

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

protected:


private:


public:
    UFUNCTION(BlueprintImplementableEvent)
        void TDOpenLevel();

protected:


private:


};
