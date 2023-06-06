#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TDMainMenu.generated.h"

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
        class UTDButton* normalMode;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        class UTDButton* infiniteMode;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        class UTDButton* graphics;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        class UTDButton* sound;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        class UTDButton* input;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        class UTDButton* exit; 

protected:


private:


public:
    UFUNCTION(BlueprintImplementableEvent)
        void TDOpenLevel();

protected:


private:


};
