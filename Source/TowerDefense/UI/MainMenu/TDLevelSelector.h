#pragma once

#include "CoreMinimal.h"
#include "UI/TDUserWidget.h"
#include "TDLevelSelector.generated.h"

class UDataTable;
class UTDButton;
class UVerticalBox;

UCLASS()
class TOWERDEFENSE_API UTDLevelSelector : public UTDUserWidget
{
    GENERATED_BODY()
public:
    virtual bool Initialize() override;
    virtual void NativePreConstruct() override;
    virtual void NativeConstruct() override;

public:
    UPROPERTY(EditDefaultsOnly)
        UDataTable* buttonsDataTable;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UVerticalBox* buttonsContainer;


protected:

private:

public:

protected:

private:
    UFUNCTION()
        void TDInitButtons();
};
