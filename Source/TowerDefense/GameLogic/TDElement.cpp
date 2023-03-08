// Fill out your copyright notice in the Description page of Project Settings.


#include "GameLogic/TDElement.h"

UTDElement::UTDElement()
{

    ElementsMap.Add(EElements::None, 1.f);
    ElementsMap.Add(EElements::Fire, 1.f);
    ElementsMap.Add(EElements::Freeze, 1.f);
    ElementsMap.Add(EElements::Plasma, 1.f);
}
