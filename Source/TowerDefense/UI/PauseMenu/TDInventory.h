#pragma once

#include "CoreMinimal.h"
#include "UI/TDUserWidget.h"
#include "TDInventory.generated.h"

class UCanvasPanel;
class UTDTextWithImage;
class UVerticalBox;
class UTDResourceCard;
class UTDTwoButtonHorizontalBox;
class UDataTable;
class UWidgetTree;

UCLASS()
class TOWERDEFENSE_API UTDInventory : public UTDUserWidget
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
        UTDTextWithImage* scrapText;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UVerticalBox* heroBPs;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UVerticalBox* towerBPs;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UVerticalBox* gems;

    UPROPERTY(EditDefaultsOnly)
        UDataTable* resourcesDataTable;

protected:


private:


public:


protected:


private:
    UFUNCTION()
    void TDInitComponents();

    UFUNCTION()
    void TDAddResourceCard(UTDResourceCard* _card, UVerticalBox* _verticalBox);

    UFUNCTION()
    void TDFillStructures();

};