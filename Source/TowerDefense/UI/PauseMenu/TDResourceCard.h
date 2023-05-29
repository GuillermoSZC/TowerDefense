#pragma once

#include "CoreMinimal.h"
#include "UI/TDUserWidget.h"
#include "TDResourceCard.generated.h"

class UImage;
class UTexture2D;

UCLASS()
class TOWERDEFENSE_API UTDResourceCard : public UTDUserWidget
{
    GENERATED_BODY()
public:
    virtual bool Initialize() override;
    virtual void NativePreConstruct() override;
    virtual void NativeConstruct() override;

public:
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UImage* resourceImage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        UTexture2D* resourceTex;

protected:


private:


public:
    UFUNCTION()
        void TDSetImage(UTexture2D* _tex);

protected:


private:
};
