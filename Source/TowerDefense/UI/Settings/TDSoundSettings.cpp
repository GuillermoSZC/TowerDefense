#include "UI/Settings/TDSoundSettings.h"
#include "UI/Utilities/TDRowWithSlider.h"
#include <UMG/Public/Components/Slider.h>
#include "GameLogic/TDGameInstance.h"


bool UTDSoundSettings::Initialize()
{
    Super::Initialize();

    return true;
}

void UTDSoundSettings::NativePreConstruct()
{
    Super::NativePreConstruct();

}

void UTDSoundSettings::NativeConstruct()
{
    Super::NativeConstruct();



    sfxRowSlider->customSlider->OnValueChanged.AddDynamic(this, &UTDSoundSettings::TDOnsfxVolumenChange);
    MusicRowSlider->customSlider->OnValueChanged.AddDynamic(this, &UTDSoundSettings::TDOnMusicVolumenChange);
    MasterRowSlider->customSlider->OnValueChanged.AddDynamic(this, &UTDSoundSettings::TDOnMasterVolumenChange);


    TDLoadSoundConfig();




}

void UTDSoundSettings::TDLoadSoundConfig()
{
    MasterRowSlider->customSlider->SetValue(UTDGameData::TDGetGameInstance()->TDGetMasterVolumen());
    sfxRowSlider->customSlider->SetValue(UTDGameData::TDGetGameInstance()->TDGetSFXVolumen());
    MusicRowSlider->customSlider->SetValue(UTDGameData::TDGetGameInstance()->TDGetMusicVolumen());

    TDOnsfxVolumenChange(UTDGameData::TDGetGameInstance()->TDGetSFXVolumen());
    TDOnMusicVolumenChange(UTDGameData::TDGetGameInstance()->TDGetMusicVolumen());
    TDOnMasterVolumenChange(UTDGameData::TDGetGameInstance()->TDGetMasterVolumen());
}

void UTDSoundSettings::TDOnsfxVolumenChange(float _newValue)
{
    UTDGameData::TDGetGameInstance()->TDSetSFXVolumen(_newValue);
    UGameplayStatics::SetSoundMixClassOverride(GetWorld(), generalSoundMix, sfxSoundClass, UTDGameData::TDGetGameInstance()->TDGetSFXVolumen(), 1.f, 0.1f);
    UTDGameData::TDGetGameInstance()->TDSaveSoundValues();
}

void UTDSoundSettings::TDOnMusicVolumenChange(float _newValue)
{
    UTDGameData::TDGetGameInstance()->TDSetMusicVolumen(_newValue);
    UGameplayStatics::SetSoundMixClassOverride(GetWorld(), generalSoundMix, musicSoundClass, UTDGameData::TDGetGameInstance()->TDGetMusicVolumen(), 1.f, 0.1f);
    UTDGameData::TDGetGameInstance()->TDSaveSoundValues();
}

void UTDSoundSettings::TDOnMasterVolumenChange(float _newValue)
{
    UTDGameData::TDGetGameInstance()->TDSetMasterVolumen(_newValue);
    UGameplayStatics::SetSoundMixClassOverride(GetWorld(), generalSoundMix, generalSoundClass, UTDGameData::TDGetGameInstance()->TDGetMasterVolumen(), 1.f, 0.1f);
    UTDGameData::TDGetGameInstance()->TDSaveSoundValues();
}
