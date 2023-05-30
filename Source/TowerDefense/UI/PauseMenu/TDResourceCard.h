#pragma once

#include "CoreMinimal.h"
#include "UI/TDUserWidget.h"
#include "GameLogic/TDLootEnum.h"
#include "TDResourceCard.generated.h"

class UImage;
class UTexture2D;
class UTDRichTextBlock;
class UBorder;

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

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDRichTextBlock* resourceText;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UBorder* backgroundMain;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UBorder* backgroundSecondary;


protected:


private:


public:
    UFUNCTION()
        void TDSetImage(UTexture2D* _tex);

    UFUNCTION()
        void TDUpdateResource(ELootItems _item);

protected:
    UFUNCTION()
        FText TDGetTextFromItem(ELootItems _item);

    UFUNCTION()
        void TDUpdateInventoryToText(UTDRichTextBlock* _text, ELootItems _item);



private:
};
