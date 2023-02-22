// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TDBase.generated.h"

UCLASS()
class TOWERDEFENSE_API ATDBase : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ATDBase(const FObjectInitializer& ObjectInitializer);

public:


protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

private:
    UPROPERTY(Category = "BaseBuild", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
        class UBoxComponent* BoxCollision;

    UPROPERTY(Category = "BaseBuild", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
        class UStaticMeshComponent* BaseStaticMesh;

    static FName BoxComponentName;

    static FName StaticMeshName;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

protected:


private:


};
