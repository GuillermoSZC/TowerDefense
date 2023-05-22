#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TDBaseButton.h"
#include "TDComposedButton.generated.h"

class UTDTextWithImage;

UCLASS()
class TOWERDEFENSE_API UTDComposedButton : public UUserWidget
{
    GENERATED_BODY()
public:
    virtual bool Initialize() override;
    virtual void NativePreConstruct() override;
    virtual void NativeConstruct() override;

public:
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDBaseButton* imgButton;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDTextWithImage* scrap;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDTextWithImage* bps;

protected:

private:

public:

protected:

private:

};
