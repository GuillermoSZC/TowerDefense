#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TDBaseButton.h"
#include "TDComposedButton.generated.h"

class UTDTextWithImage;
class UVerticalBox;
class UCanvasPanel;
class UBorder;
class UImage;

UENUM()
enum ETDResources
{
    ScrapAndBlueprints,
    Gems
};

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
        UCanvasPanel* canvasMain;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDBaseButton* imgButton;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UImage* upgrade;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UImage* customImage;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance|Custom properties")
        class UTexture2D* bpTexture = nullptr;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance|Custom properties")
        class UTexture2D* gemTexture = nullptr;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance|Custom properties")
        class UTexture2D* buttonTexture = nullptr;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDTextWithImage* scrap;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDTextWithImage* gems;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDTextWithImage* bps;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UBorder* borderBckgText;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UCanvasPanel* canvasText;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UVerticalBox* verticalContainer;

    UPROPERTY(EditAnywhere, Category = "Resources|Config")
        TEnumAsByte<ETDResources> resources;

    UPROPERTY(EditDefaultsOnly, Category = "Resources|Config")
        FLinearColor AvalibleBuyColor;

    UPROPERTY(EditDefaultsOnly, Category = "Resources|Config")
        FLinearColor NotAvalibleBuyColor;


            UPROPERTY(BlueprintReadOnly)
    TObjectPtr<USoundBase> Sound;

protected:

private:

public:
    UFUNCTION()
        void TDCanAfford(bool _CanAfford);

    UFUNCTION()
        void TDSetButtonTexture(UTexture2D* _texture);

    UFUNCTION()
        void TDSetButtonBackground(FLinearColor _color);

    UFUNCTION()
        void TDOnHovered();

    void TDSetSound(TObjectPtr<USoundBase> _Sound);


protected:

private:

};
