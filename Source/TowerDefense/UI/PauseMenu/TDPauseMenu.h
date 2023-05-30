#pragma once

#include "CoreMinimal.h"
#include "UI/TDUserWidget.h"
#include "TDPauseMenu.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUIUpdateResourcesSignature);

class UTDInventory;

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
        UTDInventory* inventory;

protected:
    FUIUpdateResourcesSignature FUIUpdateResourcesDelegate;

private:


public:


protected:
    UFUNCTION()
        virtual void TDOnVisibilityChange(ESlateVisibility _visible);


private:
    UFUNCTION()
        void TDUpdateCards();

};
