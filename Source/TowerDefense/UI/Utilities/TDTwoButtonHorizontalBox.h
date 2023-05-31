#pragma once

#include "CoreMinimal.h"
#include "Components/HorizontalBox.h"
#include "TDTwoButtonHorizontalBox.generated.h"

class UTDComposedButton;

UCLASS()
class TOWERDEFENSE_API UTDTwoButtonHorizontalBox : public UHorizontalBox
{
    GENERATED_BODY()
public:

public:
    UPROPERTY(EditDefaultsOnly)
        int childCount = 2;
protected:

private:

public:
    UFUNCTION(BlueprintCallable)
        bool TDAddButton(UUserWidget* _component);

protected:

private:


};
