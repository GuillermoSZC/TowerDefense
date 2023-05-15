// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/TDCharacter.h"
#include "TDPlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API ATDPlayerCharacter : public ATDCharacter
{
	GENERATED_BODY()
	
public:

	ATDPlayerCharacter();


 


public:


    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability System")
        UDataTable* statsDatatable;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability System")
        TArray<TSubclassOf<UGameplayAbility>> abiliyList;


    UPROPERTY(EditAnywhere,BlueprintReadWrite)
    UStaticMeshComponent* SwordMesh;



protected:



private:





public:

    virtual void Tick(float DeltaTime) override;

    UFUNCTION()
    void TDUpdateRoundValues(int32 _Rounds);

protected:

    virtual void BeginPlay() override;

   
    void TDInitialize();
private:


    void PostInitializeComponents() override;

};
