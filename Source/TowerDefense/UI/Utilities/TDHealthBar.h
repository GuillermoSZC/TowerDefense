#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TDHealthBar.generated.h"

/**
 *
 */
UCLASS()
class TOWERDEFENSE_API UTDHealthBar : public UUserWidget
{
    GENERATED_BODY()
public:
    virtual bool Initialize() override;
    virtual void NativePreConstruct() override;
    virtual void NativeConstruct() override;

public:
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        class UProgressBar* healthBar;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance|Progress Bar Settings|Scale")
        FVector2D healthBarScale = FVector2D(100, 40);

protected:

private:

public:
    UFUNCTION(BlueprintCallable)
        void TDSetBarPercentage(float _percentage, float _actualHP);


    UFUNCTION(BlueprintCallable)
        void TDSetHealthBarSize(FVector2D& _value);

protected:

private:


};
