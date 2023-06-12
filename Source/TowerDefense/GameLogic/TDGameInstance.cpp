#include "TDGameInstance.h"
#include <Kismet/GameplayStatics.h>
#include "TDGameData.h"
#include "SaveGame/TDSettingsSaveGame.h"

UTDGameInstance::UTDGameInstance()
    : isInfiniteMap(false)
{

}

void UTDGameInstance::Init()
{
    Super::Init();    
    UTDGameData::TDSetGameInstance(this);

    UTDSettingsSaveGame* SaveGameInstance = nullptr;       

    SaveGameInstance = Cast<UTDSettingsSaveGame>(UGameplayStatics::LoadGameFromSlot("ConfigSlot", 0));

    if (SaveGameInstance == nullptr)
    {
        SaveGameInstance = Cast<UTDSettingsSaveGame>(UGameplayStatics::CreateSaveGameObject(UTDSettingsSaveGame::StaticClass()));
        SaveGameInstance->sfxVolumen = 0.5f;
        SaveGameInstance->musicVolumen = 0.5f;
        SaveGameInstance->masterVolumen = 0.5f;
        UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("ConfigSlot"), 0);
    }

    musicVolumen = SaveGameInstance->musicVolumen;
    sfxVolumen = SaveGameInstance->sfxVolumen;
    masterVolumen = SaveGameInstance->masterVolumen;

}



void UTDGameInstance::TDOpenMap(UObject* _world)
{
    UGameplayStatics::OpenLevelBySoftObjectPtr(_world, worldRef, true);
}

void UTDGameInstance::TDSetMusicVolumen(float _newValue)
{
    musicVolumen = _newValue;
}

float UTDGameInstance::TDGetMusicVolumen()
{
    return musicVolumen;
}

void UTDGameInstance::TDSetSFXVolumen(float _newValue)
{
    sfxVolumen = _newValue;
}

float UTDGameInstance::TDGetSFXVolumen()
{
    return sfxVolumen;
}

void UTDGameInstance::TDSetMasterVolumen(float _newValue)
{
    masterVolumen = _newValue;
}

float UTDGameInstance::TDGetMasterVolumen()
{
    return masterVolumen;
}

void UTDGameInstance::TDSaveSoundValues()
{

    UTDSettingsSaveGame* SaveGameInstance = Cast<UTDSettingsSaveGame>(UGameplayStatics::CreateSaveGameObject(UTDSettingsSaveGame::StaticClass()));

    SaveGameInstance->sfxVolumen = sfxVolumen;
    SaveGameInstance->musicVolumen = musicVolumen;
    SaveGameInstance->masterVolumen = masterVolumen;

    UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("ConfigSlot"), 0);



}
