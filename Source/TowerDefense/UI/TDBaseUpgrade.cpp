// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TDBaseUpgrade.h"
#include "Utilities/TDButton.h"
#include "Map/TDBase.h"



bool UTDBaseUpgrade::Initialize()
{
    Super::Initialize();

    return true;
}

void UTDBaseUpgrade::NativePreConstruct()
{
    Super::NativePreConstruct();


}

void UTDBaseUpgrade::NativeConstruct()
{
    Super::NativeConstruct();

    plasmaUpgrade->ownerButton->OnClicked.AddDynamic(this, &UTDBaseUpgrade::TDPlasmaUpgrade);
    fireUpgrade->ownerButton->OnClicked.AddDynamic(this, &UTDBaseUpgrade::TDFireUpgrade);
    iceUpgrade->ownerButton->OnClicked.AddDynamic(this, &UTDBaseUpgrade::TDIceUpgrade);
    healthUpgrade->ownerButton->OnClicked.AddDynamic(this, &UTDBaseUpgrade::TDHealthUpgrade);
    speedUpgrade->ownerButton->OnClicked.AddDynamic(this, &UTDBaseUpgrade::TDSpeedUpgrade);
    damageUpgrade->ownerButton->OnClicked.AddDynamic(this, &UTDBaseUpgrade::TDDamageUpgrade);
    exit->ownerButton->OnClicked.AddDynamic(this, &UTDBaseUpgrade::TDCloseUI);
}

ATDBase* UTDBaseUpgrade::TDGetOwner()
{
    return owner;
}

void UTDBaseUpgrade::TDSetOwner(ATDBase* _owner)
{
    owner = _owner;
}

void UTDBaseUpgrade::TDPlasmaUpgrade()
{
    
}

void UTDBaseUpgrade::TDFireUpgrade()
{

}

void UTDBaseUpgrade::TDIceUpgrade()
{

}

void UTDBaseUpgrade::TDHealthUpgrade()
{

}

void UTDBaseUpgrade::TDSpeedUpgrade()
{

}

void UTDBaseUpgrade::TDDamageUpgrade()
{

}

void UTDBaseUpgrade::TDCloseUI()
{
    if (owner)
    {
        owner->TDHideUI();
    }
}
