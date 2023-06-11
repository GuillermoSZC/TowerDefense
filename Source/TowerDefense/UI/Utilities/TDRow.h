#pragma once

#include "CoreMinimal.h"
#include "UI/TDUserWidget.h"
#include "TDRow.generated.h"

class UTDRichTextBlock;
class USpacer;

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
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UTDRichTextBlock* richText;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        USpacer* customSpacer;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom Properties")
        FVector2D spacerSize = FVector2D(300.f, 1.f);

protected:

private:

public:

protected:

private:

};
