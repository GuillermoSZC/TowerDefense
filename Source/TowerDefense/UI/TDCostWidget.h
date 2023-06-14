#pragma once

#include "CoreMinimal.h"
#include "GameLogic/TDLootEnum.h"
#include "TDUserWidget.h"
#include "TDCostWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUICostUpdateSignature);

class UTDWidgetShopComponent;
class UTDComposedButton;

UCLASS()
class TOWERDEFENSE_API UTDCostWidget : public UTDUserWidget
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

        UPROPERTY(EditAnywhere)
    TObjectPtr<USoundBase> Sound;

        TArray<UTDComposedButton*> buttonsArray;

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

    void TDUpdateGemCost(UTDComposedButton* _button, ELootItems _item);
    //void TDUpdateBPCost(UTDComposedButton* _button);
    void TDUpdateBPCostWithItem(UTDComposedButton* _button, ELootItems _item = ELootItems::None);

    UFUNCTION()
        FText TDGetTextFromItem(ELootItems _item);

    UFUNCTION()
    void TDUpdateInventoryToText(UTDTextWithImage* _text, ELootItems _item);

    void TDSetSoundToButtons();

private:


};
