#pragma once

#include "CoreMinimal.h"
#include "UI/TDUserWidget.h"
#include "TDRow.generated.h"

/**
    Row parent
 */
UCLASS()
class TOWERDEFENSE_API UTDRow : public UTDUserWidget
{
    GENERATED_BODY()
public:
    virtual bool Initialize() override;
    virtual void NativePreConstruct() override;
    virtual void NativeConstruct() override;

public:

protected:

private:

public:

protected:

private:

};
