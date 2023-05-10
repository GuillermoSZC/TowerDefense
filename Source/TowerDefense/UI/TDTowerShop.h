#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TDTowerShop.generated.h"

class UTDButton;
class ATDTowerStructure;

UCLASS()
class TOWERDEFENSE_API UTDTowerShop : public UUserWidget
{
    GENERATED_BODY()
public:
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


protected:

private:
    UPROPERTY(Transient)
        ATDTowerStructure* owner;

public:
    UFUNCTION()
        void TDSetOwnerRef(ATDTowerStructure* _value);

    UFUNCTION()
        ATDTowerStructure* TDGetOwnerRef();


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
};
