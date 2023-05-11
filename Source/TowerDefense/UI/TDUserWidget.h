#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TDUserWidget.generated.h"

UCLASS()
class TOWERDEFENSE_API UTDUserWidget : public UUserWidget
{
    GENERATED_BODY()
public:
    virtual bool Initialize() override;
    virtual void NativePreConstruct() override;
    virtual void NativeConstruct() override;

public:


protected:
    UPROPERTY(Transient)
        AActor* owner;

private:

public:
    UFUNCTION()
        AActor* TDGetOwner();

    UFUNCTION()
        void TDSetOwner(AActor* _owner);

protected:


private:


};
