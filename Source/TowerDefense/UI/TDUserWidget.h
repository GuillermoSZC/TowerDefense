#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TDUserWidget.generated.h"

class UTDWidgetShopComponent;

UCLASS()
class TOWERDEFENSE_API UTDUserWidget : public UUserWidget
{
    GENERATED_BODY()
public:
    virtual bool Initialize() override;
    virtual void NativePreConstruct() override;
    virtual void NativeConstruct() override;

public:


protected:
    UPROPERTY(Transient)
        UTDWidgetShopComponent* owner;

private:

public:
    UFUNCTION()
        UTDWidgetShopComponent* TDGetOwner();

    UFUNCTION()
        void TDSetOwner(UTDWidgetShopComponent* _owner);

protected:


private:


};
