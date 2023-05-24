#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TDBaseButton.h"
#include "TDComposedButton.generated.h"

class UTDTextWithImage;
class UVerticalBox;
class UCanvasPanel;
class UBorder;

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
        UTDTextWithImage* scrap;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDTextWithImage* gems;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDTextWithImage* bps;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UBorder* borderBase;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UBorder* borderBckgText;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UCanvasPanel* canvasText;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UVerticalBox* verticalContainer;

    UPROPERTY(EditAnywhere, Category = "Resources|Config")
        TEnumAsByte<ETDResources> resources;

protected:

private:

public:

protected:

private:

};
