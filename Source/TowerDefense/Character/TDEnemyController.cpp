// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TDEnemyController.h"
#include "AIModule/Classes/BehaviorTree/BlackboardComponent.h"

ATDEnemyController::ATDEnemyController()
{

    waypointRef = nullptr;
}

void ATDEnemyController::BeginPlay()
{
    Super::BeginPlay();
    

    //UBlackboardComponent* blackboard = GetBlackboardComponent();

   // blackboard->SetValueAsObject(FName(TEXT("WaypointActor")), waypointRef);
//    blackboard->SetValueAsVector(FName(TEXT("WaypointPosition")), waypointRef->GetActorLocation());

}

