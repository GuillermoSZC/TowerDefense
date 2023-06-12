#pragma once

#include "CoreMinimal.h"
#include "UI/TDUserWidget.h"
#include "TDSoundSettings.generated.h"

class UTDRowWithSlider;

UCLASS()
class TOWERDEFENSE_API UTDSoundSettings : public UTDUserWidget
{
    GENERATED_BODY()
public:
    virtual bool Initialize() override;
    virtual void NativePreConstruct() override;
    virtual void NativeConstruct() override;

public:


        UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDRowWithSlider* MasterRowSlider;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDRowWithSlider* sfxRowSlider;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDRowWithSlider* MusicRowSlider;


    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        USoundMix* generalSoundMix;


    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        USoundClass* generalSoundClass;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        USoundClass* musicSoundClass;


    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        USoundClass* sfxSoundClass;





protected:


private:


public:


protected:


private:


    void TDLoadSoundConfig();

    UFUNCTION()
    void TDOnsfxVolumenChange(float _newValue);
    UFUNCTION()
    void TDOnMusicVolumenChange(float _newValue);
    UFUNCTION()
    void TDOnMasterVolumenChange(float _newValue);
};
