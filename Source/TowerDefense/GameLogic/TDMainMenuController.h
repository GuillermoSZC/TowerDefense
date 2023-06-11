#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TDMainMenuController.generated.h"

class UTDMainMenu;

UCLASS()
class TOWERDEFENSE_API ATDMainMenuController : public APlayerController
{
    GENERATED_BODY()
public:


public:
    UPROPERTY(EditDefaultsOnly)
        TSubclassOf<UTDMainMenu> mainMenuClass;

protected:
    UPROPERTY(Transient)
        UTDMainMenu* mainMenuRef;

private:


public:


protected:
    void BeginPlay() override;

private:

};
