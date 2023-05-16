#pragma once

#include "CoreMinimal.h"
#include "TDUserWidget.h"
#include "GameLogic/TDTowerEnum.h"
#include "Map/TDTower.h"
#include "TDTowerShop.generated.h"

class UTDButton;

UCLASS()
class TOWERDEFENSE_API UTDTowerShop : public UTDUserWidget
{
    GENERATED_BODY()
public:
    UTDTowerShop(const FObjectInitializer& ObjectInitializer);

    virtual bool Initialize() override;
    virtual void NativePreConstruct() override;
    virtual void NativeConstruct() override;

public:
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDButton* balisticButton;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDButton* sonicButton;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDButton* deadRayButton;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDButton* movementButton;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDButton* attackButton;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDButton* exitButton;

    UPROPERTY(EditDefaultsOnly)
        TMap<ETowers, TSubclassOf<ATDTower>> towerMap;

protected:

private:

public:

protected:

private:
#pragma region BUTTON_IMPLEMENTATION
    UFUNCTION()
        void TDBalisticSpawn();

    UFUNCTION()
        void TDSonicSpawn();

    UFUNCTION()
        void TDDeadRaySpawn();

    UFUNCTION()
        void TDMovementSpawn();

    UFUNCTION()
        void TDAttackSpawn();

    UFUNCTION()
        void TDCloseUI();
#pragma endregion

    UFUNCTION()
        void TDSpawnLogic(ETowers _tower);

    UFUNCTION()
        void TDEndSpawnLogic();

};
