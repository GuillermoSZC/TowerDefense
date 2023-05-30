#pragma once

#include "CoreMinimal.h"
#include <Engine/DataTable.h>
#include "TDResourceCardParameters.generated.h"

USTRUCT(BlueprintType)
struct FTDResourceCardParameters : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FText resourceText;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        UTexture2D* image;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FLinearColor color;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FVector2D cardSize;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        float verticalPadding;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        float horizontalPadding;

};
