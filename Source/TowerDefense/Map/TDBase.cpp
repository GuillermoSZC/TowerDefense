// Fill out your copyright notice in the Description page of Project Settings.


#include "TDBase.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

FName ATDBase::BoxComponentName(TEXT("BoxComponentName"));
FName ATDBase::StaticMeshName(TEXT("BaseMesh"));

ATDBase::ATDBase(const FObjectInitializer& ObjectInitializer)
{
    PrimaryActorTick.bCanEverTick = true;

    BoxCollision = CreateDefaultSubobject<UBoxComponent>(ATDBase::BoxComponentName);
    BoxCollision->SetBoxExtent(FVector(32.f, 32.f, 32.f));

    RootComponent = BoxCollision;

    BaseStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(ATDBase::StaticMeshName);
    BaseStaticMesh->AttachToComponent(BoxCollision, FAttachmentTransformRules::KeepRelativeTransform);
    

}

// Called when the game starts or when spawned
void ATDBase::BeginPlay()
{
    Super::BeginPlay();

}

// Called every frame
void ATDBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

