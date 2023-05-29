#include "UI/PauseMenu/TDResourceCard.h"
#include <Engine/Texture2D.h>
#include <UMG/Public/Components/Image.h>

bool UTDResourceCard::Initialize()
{
    Super::Initialize();

    return true;
}

void UTDResourceCard::NativePreConstruct()
{
    Super::NativePreConstruct();

    TDSetImage(resourceTex);
}

void UTDResourceCard::NativeConstruct()
{
    Super::NativeConstruct();

}

void UTDResourceCard::TDSetImage(UTexture2D* _tex)
{
    if (IsValid(_tex))
    {
        resourceTex = _tex;
        resourceImage->SetBrushFromTexture(resourceTex);
    }
}
