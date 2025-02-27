



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



TArray<ATDEnemy*>  UTDWeightManager::TDSetActualRound(int32& _atualRound, TArray<EElements> _roundElement)
{
    actualRoundElements.Empty();
    actualRoundElements = _roundElement;
    ActualRound = _atualRound;
    WeightPerRound = ActualRound * 10;
    actualWegith = 0;
    enemiesPerClass.Empty();
    TArray<ATDEnemy*> preparedEnemies;

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

    return preparedEnemies;
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
    if (_enemyRef->DynamicMaterial)
    {
        _enemyRef->DynamicMaterial->ConditionalBeginDestroy();
    }

    if (Row.material)
    {
        _enemyRef->GetMesh()->SetMaterial(0, Row.material);
        _enemyRef->DynamicMaterial = _enemyRef->GetMesh()->CreateDynamicMaterialInstance(0, _enemyRef->GetMesh()->GetMaterial(0));
    }
    else
    {
        TArray<FSkeletalMaterial> SKMaterials;
        SKMaterials =  Row.enemyMesh.LoadSynchronous()->GetMaterials();
        _enemyRef->GetMesh()->SetMaterial(0, SKMaterials[0].MaterialInterface);
        _enemyRef->DynamicMaterial = _enemyRef->GetMesh()->CreateDynamicMaterialInstance(0, _enemyRef->GetMesh()->GetMaterial(0));
    }
    _enemyRef->GetMesh()->SetRelativeLocation(Row.MeshPosition);
    _enemyRef->GetMesh()->SetRelativeScale3D(Row.MeshScale);
    _enemyRef->GetMesh()->SetAnimInstanceClass(Row.animationBlueprint);
    _enemyRef->TDSetAnimMontaje(Row.animationMontaje.LoadSynchronous());
    _enemyRef->GetCapsuleComponent()->SetCapsuleRadius(Row.capsuleRadius);
    _enemyRef->GetCapsuleComponent()->SetCapsuleHalfHeight(Row.capsuleHeight);


    //GAS
    _enemyRef->movementVariation = Row.movementVariation;
    _enemyRef->abiliyList = Row.abiliyAsset->abiliyList;
    _enemyRef->enemyAttribute = Row.enemyAttribute;

    //Weapon
    if (!Row.WeaponAssetArray.IsEmpty())
    {
        int32 x = FMath::Rand() % Row.WeaponAssetArray.Num();
        UTDweaponDataAsset* WeaponAsset = Row.WeaponAssetArray[x];
        _enemyRef->weaponAssetRef = WeaponAsset;
        FAttachmentTransformRules rules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, false);

        if (WeaponAsset->assetClass == AssetType::SkeletalMesh)
        {
            _enemyRef->skeletalWeaponComponent->Activate();
            _enemyRef->skeletalWeaponComponent->SetSkeletalMesh(WeaponAsset->skeletalWeaponMesh.LoadSynchronous());
            _enemyRef->StaticWeaponComponent->SetStaticMesh(nullptr);
            _enemyRef->skeletalWeaponComponent->AttachToComponent(_enemyRef->GetMesh(), rules, WeaponAsset->SocketName);
            _enemyRef->StaticWeaponComponent->Deactivate();

        }
        else if (WeaponAsset->assetClass == AssetType::StaticMesh)
        {
            _enemyRef->StaticWeaponComponent->Activate();
            _enemyRef->StaticWeaponComponent->SetStaticMesh(WeaponAsset->StaticWeaponMesh.LoadSynchronous());
            _enemyRef->skeletalWeaponComponent->SetSkeletalMesh(nullptr);
            _enemyRef->StaticWeaponComponent->AttachToComponent(_enemyRef->GetMesh(), rules, WeaponAsset->SocketName);
            _enemyRef->skeletalWeaponComponent->Deactivate();

        }
        else
        {
            _enemyRef->StaticWeaponComponent->SetStaticMesh(nullptr);
            _enemyRef->skeletalWeaponComponent->SetSkeletalMesh(nullptr);

            _enemyRef->skeletalWeaponComponent->Deactivate();
            _enemyRef->StaticWeaponComponent->Deactivate();
        }

//         if (WeaponAsset->weaponAbility)
//         {
//             _enemyRef->abilitySystem->GiveAbility(FGameplayAbilitySpec(WeaponAsset->weaponAbility.GetDefaultObject(), 1, 0));
//         }
    }
    else
    {
        _enemyRef->StaticWeaponComponent->SetStaticMesh(nullptr);
        _enemyRef->skeletalWeaponComponent->SetSkeletalMesh(nullptr);
        _enemyRef->skeletalWeaponComponent->Deactivate();
        _enemyRef->StaticWeaponComponent->Deactivate();
    }

    //Weight
    _enemyRef->unitWeight = Row.weight;

    //AI
    ATDEnemyController* enemyController = _enemyRef->GetController<ATDEnemyController>();

    if (enemyController)
    {
        enemyController->GetBlackboardComponent()->ClearValue("BaseBuild");
        enemyController->GetBlackboardComponent()->ClearValue("WaypointPosition");
        enemyController->GetBlackboardComponent()->ClearValue("WaypointActor");
        enemyController->GetBlackboardComponent()->ClearValue("RealBasePosition");
        enemyController->RunBehaviorTree(Row.behaviorTree.LoadSynchronous());
    }


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

