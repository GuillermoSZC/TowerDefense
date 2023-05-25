



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
#include "UI/Utilities/TDHealthBar.h"
#include "Components/WidgetComponent.h"
#include "GameplayAbilitySpec.h"
#include "AbilitySystemComponent.h"

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
    enemiesPerClass.Empty();


    ATDObjectPooler* objectRef = UTDGameData::TDGetObjectPooler();
    ensure(objectRef);

    while (!(actualWegith >= WeightPerRound))
    {
        ATDEnemy* actualEnemy = objectRef->TDGetEnemyFromPool();

        if (actualEnemy)
        {
            FTDEnemiesDataTable* Row = TDSelectRandomRowFromDataTable();
            TDSetEnemyValues(actualEnemy, *Row);
            preparedEnemies.Add(actualEnemy);
        }
    }

    return preparedEnemies.Num();
}



void UTDWeightManager::TDGetRowFromDataTable(FName _RowName, FTDEnemiesDataTable& _Row)
{
    if (enemiesDatatable)
    {
        FString ContextString = TEXT("Data table context");
        TArray<FName> RowNames = enemiesDatatable->GetRowNames();
        FTDEnemiesDataTable* temp = enemiesDatatable->FindRow<FTDEnemiesDataTable>(_RowName, ContextString, true);
        _Row = *(temp);
    }
}

void UTDWeightManager::TDSpawnEnemy()
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
        spawnerRef->TDPlaceEnemy(actualEnemy);
        actualEnemy->TDSetActive();
    }

}

void UTDWeightManager::TDSetDataTable(UDataTable* _ref)
{
    enemiesDatatable = _ref;
}



FTDEnemiesDataTable* UTDWeightManager::TDSelectRandomRowFromDataTable()
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
                //check if the selected enemy's weight is more than the limit weight
                loop = Row->weight != -1 && ActualRound >= Row->firstPossibleApperance && WeightPerRound >= actualWegith + Row->weight;

                //check if there
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
                    return Row;
                }
            }
        }

    }
    return nullptr;
}

void UTDWeightManager::TDSetEnemyValues(ATDEnemy* _enemyRef, FTDEnemiesDataTable& Row)
{

    //Debug

    _enemyRef->DebugString = Row.DebugName;


    //Mesh and anim 
    _enemyRef->GetMesh()->SetSkeletalMesh(Row.enemyMesh.LoadSynchronous());
    if (Row.material)
    {
        _enemyRef->GetMesh()->SetMaterial(0, Row.material);
    }
    else
    {
        TArray<FSkeletalMaterial> SKMaterials;
        SKMaterials =  Row.enemyMesh.LoadSynchronous()->GetMaterials();
        _enemyRef->GetMesh()->SetMaterial(0, SKMaterials[0].MaterialInterface);
    }
    _enemyRef->GetMesh()->SetRelativeLocation(Row.MeshPosition);
    _enemyRef->GetMesh()->SetRelativeScale3D(Row.MeshScale);
    _enemyRef->GetMesh()->SetAnimInstanceClass(Row.animationBlueprint);
    _enemyRef->TDSetAnimMontaje(Row.animationMontaje.LoadSynchronous());
    _enemyRef->GetCapsuleComponent()->SetCapsuleRadius(Row.capsuleRadius);
    _enemyRef->GetCapsuleComponent()->SetCapsuleHalfHeight(Row.capsuleHeight);


    //GAS
//     _enemyRef->healthDatatable = Row.EnemyStatsDataAsset->healthDataTable;
//     _enemyRef->damageDatatable = Row.EnemyStatsDataAsset->damageDataTable;
//     _enemyRef->movementDatatable = Row.EnemyStatsDataAsset->movementDataTable;
    _enemyRef->movementVariation = Row.movementVariation;
    _enemyRef->abiliyList = Row.abiliyAsset->abiliyList;
    _enemyRef->enemyAttribute = Row.enemyAttribute;

    //Weapon
    if (Row.WeaponAsset)
    {
        FAttachmentTransformRules rules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, false);

        if (Row.WeaponAsset->assetClass == AssetType::SkeletalMesh)
        {
            _enemyRef->skeletalWeaponComponent->SetSkeletalMesh(Row.WeaponAsset->skeletalWeaponMesh.LoadSynchronous());
            _enemyRef->skeletalWeaponComponent->AttachToComponent(_enemyRef->GetMesh(), rules, Row.WeaponAsset->SocketName);
        }
        else if (Row.WeaponAsset->assetClass == AssetType::StaticMesh)
        {
            _enemyRef->StaticWeaponComponent->SetStaticMesh(Row.WeaponAsset->StaticWeaponMesh.LoadSynchronous());
            _enemyRef->StaticWeaponComponent->AttachToComponent(_enemyRef->GetMesh(), rules, Row.WeaponAsset->SocketName);
        }

        if (Row.WeaponAsset->weaponAbility)
        {
            _enemyRef->abilitySystem->GiveAbility(FGameplayAbilitySpec(Row.WeaponAsset->weaponAbility.GetDefaultObject(), 1, 0));
        }
    }

    //Weight
    _enemyRef->unitWeight = Row.weight;

    //AI
    ATDEnemyController* enemyController = _enemyRef->GetController<ATDEnemyController>();
    enemyController->RunBehaviorTree(Row.behaviorTree.LoadSynchronous());

    //UI
    _enemyRef->TDGetHealthBarReference()->TDSetHealthBarSize(Row.HealthBarSize);
    _enemyRef->TDGetHealthWidgetComponent()->SetRelativeLocation(Row.HealthBarPosition);


    //Element
    int y = FMath::Rand() % actualRoundElements.Num();
    UTDElementComponent* temp = ITDInterface::Execute_TDGetElementComponent(_enemyRef);
    temp->TDSetSpawnedElement(actualRoundElements[y]);



    //Loot
    UDataTable* lootTable = UTDGameData::TDGetGameMode()->TDGetDataLootFromElement(actualRoundElements[y]);
    _enemyRef->TDSetLootDataTable(lootTable);

    if (Row.chanceDataTable)
    {
        _enemyRef->TDSetChanceDataTable(Row.chanceDataTable);
    }

}

