#pragma once

#include "CoreMinimal.h"
#include "UI/TDUserWidget.h"
#include "TDCustomSlider.generated.h"

class USlider;
class UProgressBar;

UCLASS()
class TOWERDEFENSE_API UTDCustomSlider : public UTDUserWidget
{
    GENERATED_BODY()
public:
    virtual bool Initialize() override;
    virtual void NativePreConstruct() override;
    virtual void NativeConstruct() override;

public:
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        USlider* customSlider;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UProgressBar* customProgressBar;

protected:


private:


public:
    UFUNCTION()
        void TDUpdateValue(float _value);

protected:


private:


};
