#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TDMainMenu.generated.h"

/**
 *
 */
UCLASS()
class TOWERDEFENSE_API UTDMainMenu : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual bool Initialize() override;
    virtual void NativePreConstruct() override;
    virtual void NativeConstruct() override;


public:
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        class UTDButton* playButton;

protected:


private:


public:
    UFUNCTION(BlueprintImplementableEvent)
        void TDOpenLevel();

protected:


private:


};
