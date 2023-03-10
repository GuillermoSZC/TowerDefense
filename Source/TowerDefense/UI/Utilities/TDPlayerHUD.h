// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TDPlayerHUD.generated.h"

/**
 *
 */
UCLASS()
class TOWERDEFENSE_API UTDPlayerHUD : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual bool Initialize() override;
    virtual void NativePreConstruct() override;
    virtual void NativeConstruct() override;

public:
    //  @TODO: PREGUNTAR DISEÑO
    //     UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    //         class NUMERO RONDAS

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        class UImage* firstElement;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        class UImage* secondElement;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        class UImage* thirdElement;

    // @TODO: MINIMAPA - INVESTIGAR EL ASSET DE LA EPIC
    /**
     *
     */

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        class UTDText* timer;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        class UTDText* phase;

    // @TODO: BARRA DE VIDA - COMPONENTE NUEVO? - PREGUNTAR DISEÑO
    /**
    *
    * Elementos de encima de la barra de vida??
    *
    * UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        class UImage* playerElement;
    */

#pragma region HUD_INVENTORY
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        class UTDTextWithImage* scrap;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        class UTDTextWithImage* swordBlueprint;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        class UTDTextWithImage* armorBlueprint;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        class UTDTextWithImage* bootsBlueprint;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        class UTDTextWithImage* ballistaBlueprint;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        class UTDTextWithImage* sonicTowerBlueprint;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        class UTDTextWithImage* deathRayTowerBlueprint;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        class UTDTextWithImage* speedTowerBlueprint;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        class UTDTextWithImage* damageTowerBlueprint;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        class UTDTextWithImage* fireGem;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        class UTDTextWithImage* iceGem;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        class UTDTextWithImage* plasmaGem;
#pragma endregion

protected:


private:


public:


protected:


private:


};
