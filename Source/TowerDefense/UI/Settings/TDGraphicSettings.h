#pragma once

#include "CoreMinimal.h"
#include "UI/TDUserWidget.h"
#include "TDGraphicSettings.generated.h"

class UTDRowStringList;
class UGameUserSettings;

UCLASS()
class TOWERDEFENSE_API UTDGraphicSettings : public UTDUserWidget
{
    GENERATED_BODY()
public:
    virtual bool Initialize() override;
    virtual void NativePreConstruct() override;
    virtual void NativeConstruct() override;

public:
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDRowStringList* screenMode;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDRowStringList* resolution;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDRowStringList* frameCap;



protected:


private:
    UPROPERTY(Transient)
        UGameUserSettings* gameUserSettings;

public:
    UFUNCTION()
        void TDOnScreenModeChanged(FString _string, ESelectInfo::Type _select);

    UFUNCTION()
        void TDOnResolutionChanged(FString _string, ESelectInfo::Type _select);

    UFUNCTION()
        void TDOnFrameCapChanged(FString _string, ESelectInfo::Type _select);

protected:


private:


};
