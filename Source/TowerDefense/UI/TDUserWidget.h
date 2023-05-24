#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TDUserWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUICostUpdateSignature);


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

    UPROPERTY()
        FUICostUpdateSignature FUICostUpdateDelegate;

private:

public:
    UFUNCTION()
        UTDWidgetShopComponent* TDGetOwner();

    UFUNCTION()
        void TDSetOwner(UTDWidgetShopComponent* _owner);

    UFUNCTION()
    virtual void TDOnVisibilityChange(ESlateVisibility _visible);

    UFUNCTION()
    virtual void TDUpdateCost();
    
  UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
        void TDFadeIn();

protected:

  
private:


};
