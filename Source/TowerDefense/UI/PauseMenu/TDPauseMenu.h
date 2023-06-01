#pragma once

#include "CoreMinimal.h"
#include "UI/TDUserWidget.h"
#include "TDPauseMenu.generated.h"



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

private:
    static UPROPERTY(Transient)
        UTDPauseMenu* owner;

public:
    UFUNCTION()
        static UTDPauseMenu* TDGetPauseMenuRef();

protected:
    UFUNCTION()
        virtual void TDOnVisibilityChange(ESlateVisibility _visible);


private:


};
