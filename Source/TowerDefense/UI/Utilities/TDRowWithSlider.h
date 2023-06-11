#pragma once

#include "CoreMinimal.h"
#include "UI/Utilities/TDRow.h"
#include "TDRowWithSlider.generated.h"

class USlider;

/**
    Row with Silder Properties
 */
UCLASS()
class TOWERDEFENSE_API UTDRowWithSlider : public UTDRow
{
    GENERATED_BODY()
public:
    virtual bool Initialize() override;
    virtual void NativePreConstruct() override;
    virtual void NativeConstruct() override;

public:
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        USlider* customSlider;

protected:

private:

public:

protected:

private:

};
