// Fill out your copyright notice in the Description page of Project Settings.


#include "GameLogic/TDWeightManager.h"
#include "TDGameData.h"
#include "Map/TDSpawner.h"
#include "Character/TDEnemy.h"
#include "TDObjectPooler.h"
#include "TDEnemiesDataTable.h"
#include "Character/TDEnemyController.h"
#include "AIModule/Classes/BehaviorTree/BehaviorTree.h"
#include "Components/CapsuleComponent.h"


UTDWeightManager* UTDWeightManager::weightManager = nullptr;



UTDWeightManager::UTDWeightManager()
{
    actualWegith = 0;
}


UTDWeightManager* UTDWeightManager::TDGetWeightManager()
{


    if (weightManager == nullptr)
    {
        UWorld* actualWorld = UTDGameData::TDGetWorld();
        FActorSpawnParameters paramet;
        //weightManager = actualWorld->SpawnActor<UTDWeightManager>();

        weightManager = NewObject<UTDWeightManager>(UTDWeightManager::StaticClass(), FName(TEXT("WeightManager")), EObjectFlags::RF_MarkAsRootSet);
    }

    return weightManager;

}

int32 UTDWeightManager::TDSetActualRound(int32& _atualRound)
{
    ActualRound = _atualRound;
    WeightPerRound = ActualRound * 10;
    actualWegith = 0;
    licheCounter = 0;
    enemiesPerClass.Empty();
    return WeightPerRound;
}

void UTDWeightManager::TDStartSpawn()
{
    if (actualWegith >= WeightPerRound)
    {
        ATDRoundManager::TDGetRoundManager()->TDStopRound();
        GEngine->AddOnScreenDebugMessage(0, 5.f, FColor::Orange, FString::FromInt(actualWegith));
        return;
    }

    UWorld* actualWorld = UTDGameData::TDGetWorld();


    ATDObjectPooler* objectRef = ATDObjectPooler::TDGetObjectPooler();
    ensure(objectRef);

    ATDEnemy* actualEnemy = objectRef->TDGetEnemyFromPool();

    if (actualEnemy)
    {
        TDSetEnemyValues(actualEnemy);
        ATDSpawner* spawnerRef = UTDGameData::TDGetSpanwerActor();
        spawnerRef->TDSpawnEnemy(actualEnemy);
    }

}

void UTDWeightManager::TDSetDataTable(UDataTable* _ref)
{
    enemiesDatatable = _ref;
}



void UTDWeightManager::TDSetEnemyValues(ATDEnemy* _enemyRef)
{

    if (enemiesDatatable)
    {
        FString ContextString = TEXT("Data table context");
        FTDEnemiesDataTable* Row = nullptr;
        TArray<FName> RowNames = enemiesDatatable->GetRowNames();
        bool loop = false;


        while (!loop)
        {
            int32 x = FMath::Rand() % RowNames.Num();
            FName selectedenemy = RowNames[x];

            Row = enemiesDatatable->FindRow<FTDEnemiesDataTable>(selectedenemy, ContextString, true);

//             //provisional, cambiar a algo mas escalable 
//             if (licheCounter == 3)
//             {
//                 return;
//             }
// 
//             if (selectedenemy == FName(TEXT("Lich")) && licheCounter < 3)
//             {
//                 ++licheCounter;
//             }


            if (Row)
            {
                loop = ActualRound >= Row->firstPossibleApperance && WeightPerRound >= actualWegith + Row->weight;

                if (Row->limitEnemiesPerRound >= 1)
                {
                    if (enemiesPerClass.Contains(x))
                    {
                        loop = Row->limitEnemiesPerRound > enemiesPerClass[x];
                    }
                }
                
                if (loop)
                {
                    if (enemiesPerClass.Contains(x))
                    {
                        enemiesPerClass[x] = enemiesPerClass[x] + 1;
                    }
                    else
                    {
                        enemiesPerClass.Add(x, 1);

                    }

                    actualWegith += Row->weight;

                    _enemyRef->GetMesh()->SetSkeletalMesh(Row->enemyMesh.LoadSynchronous());
                    _enemyRef->GetMesh()->SetRelativeLocation(Row->MeshPosition);
                    _enemyRef->GetMesh()->SetRelativeScale3D(Row->MeshScale);
                    _enemyRef->GetMesh()->SetAnimInstanceClass(Row->animationBlueprint);
                    _enemyRef->TDSetAnimMontaje(Row->animationMontaje.LoadSynchronous());
                    _enemyRef->statsDatatable = Row->gasDataTable;
                    _enemyRef->movementVariation = Row->movementVariation;
                    _enemyRef->GetCapsuleComponent()->SetCapsuleRadius(Row->capsuleRadius);
                    _enemyRef->GetCapsuleComponent()->SetCapsuleHalfHeight(Row->capsuleHeight);
                    _enemyRef->abiliyList = Row->abiliyList;
                    _enemyRef->unitWeight = Row->weight;
                    ATDEnemyController* enemyController = _enemyRef->GetController<ATDEnemyController>();
                    enemyController->RunBehaviorTree(Row->behaviorTree.LoadSynchronous());

                    _enemyRef->TDSetActive();

                }
            }
        }
    }
}

