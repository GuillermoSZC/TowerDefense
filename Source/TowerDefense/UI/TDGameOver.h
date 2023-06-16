#pragma once

#include "CoreMinimal.h"
#include "UI/TDUserWidget.h"
#include "TDGameOver.generated.h"

class UTDRichTextBlock;
class UWidgetAnimation;

/**
 *
 */
UCLASS()
class TOWERDEFENSE_API UTDGameOver : public UTDUserWidget
{
    GENERATED_BODY()
public:
    virtual bool Initialize() override;
    virtual void NativePreConstruct() override;
    virtual void NativeConstruct() override;

public:
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDRichTextBlock* gameOverText;

    UPROPERTY(BlueprintReadWrite, Transient, meta = (BindWidgetAnim))
        UWidgetAnimation* fadeIn;

protected:


private:


public:
    UFUNCTION(BlueprintImplementableEvent)
        void TDFadeIn();


protected:


private:
    UFUNCTION()
        void TDVisibilityGameOver(ESlateVisibility _visibility);

};
