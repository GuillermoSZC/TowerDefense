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
#include "TDElementComponent.h"
#include "TDGameMode.h"





UTDWeightManager::UTDWeightManager()
{
    actualWegith = 0;
}



int32 UTDWeightManager::TDSetActualRound(int32& _atualRound, TArray<EElements> _roundElement)
{
    actualRoundElements.Empty();
    actualRoundElements = _roundElement;
    ActualRound = _atualRound;
    WeightPerRound = ActualRound * 10;
    actualWegith = 0;
    licheCounter = 0;
    enemiesPerClass.Empty();

    UWorld* actualWorld = UTDGameData::TDGetWorld();


    ATDObjectPooler* objectRef = UTDGameData::TDGetObjectPooler();
    ensure(objectRef);

    while (!(actualWegith >= WeightPerRound))
    {
        ATDEnemy* actualEnemy = objectRef->TDGetEnemyFromPool();

        if (actualEnemy)
        {
            TDSetEnemyValues(actualEnemy);      
            preparedEnemies.Add(actualEnemy);
        }
    }

    return preparedEnemies.Num();
}



void UTDWeightManager::TDStartSpawn()
{
   
    ATDEnemy* actualEnemy = nullptr;
    if (!preparedEnemies.IsEmpty())
    {
        actualEnemy = preparedEnemies[0];
        preparedEnemies.Remove(actualEnemy);
    }  

    if (actualEnemy)
    {
        ATDSpawner* spawnerRef = UTDGameData::TDGetSpanwerActor();
        spawnerRef->TDSpawnEnemy(actualEnemy);
        actualEnemy->TDSetActive();
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
                    _enemyRef->healthDatatable = Row->healthDataTable;
                    _enemyRef->damageDatatable = Row->damageDataTable;
                    _enemyRef->movementDatatable = Row->movementDataTable;
                    _enemyRef->movementVariation = Row->movementVariation;
                    _enemyRef->GetCapsuleComponent()->SetCapsuleRadius(Row->capsuleRadius);
                    _enemyRef->GetCapsuleComponent()->SetCapsuleHalfHeight(Row->capsuleHeight);
                    _enemyRef->abiliyList = Row->abiliyList;
                    _enemyRef->unitWeight = Row->weight;
                    ATDEnemyController* enemyController = _enemyRef->GetController<ATDEnemyController>();
                    enemyController->RunBehaviorTree(Row->behaviorTree.LoadSynchronous());

                    int y = FMath::Rand() % actualRoundElements.Num();
                    UTDElementComponent* temp = ITDInterface::Execute_TDGetElementComponent(_enemyRef);

                    temp->TDSetSpawnedElement(UTDGameData::TDGetGameMode()->TDGetDataAssetFromElement(actualRoundElements[y]));

                    //_enemyRef->TDSetActive();

                }
            }
        }
    }
}

