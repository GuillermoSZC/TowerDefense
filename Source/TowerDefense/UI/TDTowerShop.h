#pragma once

#include "CoreMinimal.h"
#include "TDCostWidget.h"
#include "GameLogic/TDTowerEnum.h"
#include "Map/TDTower.h"
#include "TDTowerShop.generated.h"

class UTDTextWithImage;
class UTDComposedButton;
class UTDBaseButton;

UCLASS()
class TOWERDEFENSE_API UTDTowerShop : public UTDCostWidget
{
    GENERATED_BODY()
public:
    UTDTowerShop(const FObjectInitializer& ObjectInitializer);

    virtual bool Initialize() override;
    virtual void NativePreConstruct() override;
    virtual void NativeConstruct() override;

public:
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDComposedButton* balisticButton;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDComposedButton* sonicButton;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDComposedButton* deadRayButton;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDComposedButton* movementButton;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDComposedButton* attackButton;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDBaseButton* exitButton;

#pragma region RESOURCES
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDTextWithImage* scrap;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDTextWithImage* bpBalistic;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDTextWithImage* bpSonic;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDTextWithImage* bpDeadRay;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDTextWithImage* bpMovement;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDTextWithImage* bpDamage;
#pragma endregion

    UPROPERTY(EditDefaultsOnly)
        TMap<ETowers, TSubclassOf<ATDTower>> towerMap;

protected:

private:

public:

    void TDOnVisibilityChange(ESlateVisibility _visible) override;

protected:
    void TDUpdateCost() override;

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
