// Fill out your copyright notice in the Description page of Project Settings.


#include "GameLogic/TDRoundElementsType.h"
#include "ElementsEnum.h"

UTDRoundElementsType::UTDRoundElementsType()
{
    RandomElements.Add(EElements::Fire);
    RandomElements.Add(EElements::Freeze);
    RandomElements.Add(EElements::Plasma);
}

TArray<EElements> UTDRoundElementsType::TDGetRoundElements(TArray<EElements>& _elementsArray)
{
    

    for (EElements iter : GrantedElements)
    {
        _elementsArray.Add(iter);
    }


  

    for (int i = 0; i < numberOfRandomElements; ++i)
    {

        bool loop = false;

        while (!loop)
        {
            int x = FMath::Rand() % RandomElements.Num();

            if (!_elementsArray.Contains(RandomElements[x]))
            {
                _elementsArray.Add(RandomElements[x]);
                loop = true;
            }
        }
    }

    return _elementsArray;
}
