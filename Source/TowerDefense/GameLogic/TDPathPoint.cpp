#include "GameLogic/TDPathPoint.h"
#include "Character/TDEnemyController.h"
#include "Character/TDEnemy.h"
#include "AIModule/Classes/BehaviorTree/BlackboardComponent.h"

ATDPathPoint::ATDPathPoint()
{

}

void ATDPathPoint::BeginPlay()
{
    Super::BeginPlay();

    if (pathPointArray.Num() <= 0)
    {
        isBase = true;
    }

    if (isSpawner)
    {
        UTDGameData::TDaddSpawnerActor(this);
    }

}

void ATDPathPoint::TDArrivedAction(ATDEnemyController* _enemy)
{
    //     if (!isBase)
    //     {
    // 
    //         int arraySize = pathPointArray.Num();
    //         if (arraySize == 0)
    //         {
    //             return;
    //         }
    // 
    //         if (arraySize == 1)
    //         {
    //            
    //             _enemy->GetBlackboardComponent()->SetValueAsObject(FName(TEXT("WaypointActor")), pathPointArray[0]);
    //             _enemy->GetBlackboardComponent()->SetValueAsVector(FName(TEXT("WaypointPosition")), pathPointArray[0]->GetActorLocation());
    //             return;
    //         }        
    // 
    //         
    // 
    // 
    //         _enemy->GetBlackboardComponent()->SetValueAsObject(FName(TEXT("WaypointActor")), pathPointArray[x]);
    //         _enemy->GetBlackboardComponent()->SetValueAsVector(FName(TEXT("WaypointPosition")), pathPointArray[x]->GetActorLocation());

     //   }
}

bool ATDPathPoint::TDGetIsBase()
{
    return isBase;
}

ATDPathPoint* ATDPathPoint::TDGetNextPoint()
{

    int randomPoint = FMath::Rand() % pathPointArray.Num();
    return pathPointArray[randomPoint];

}

void ATDPathPoint::TDPlaceEnemy(ATDEnemy* _enemyRef)
{
    ATDEnemyController* enemyController = _enemyRef->GetController<ATDEnemyController>();
    UBlackboardComponent* blackboard = enemyController->GetBlackboardComponent();

    ATDPathPoint* firstWaypoint = nullptr;
    if (!pathPointArray.IsEmpty())
    {
        firstWaypoint = pathPointArray[0];

    }

    if (!firstWaypoint)
    {
        TArray<AActor*> waypointsArray;
        UGameplayStatics::GetAllActorsOfClass(UTDGameData::TDGetWorld(), ATDPathPoint::StaticClass(), waypointsArray);

        float minusDistance = MAX_FLT;
        FVector spawnerLocation = GetActorLocation();

        for (AActor* iter : waypointsArray)
        {
            float temp = FVector::Distance(iter->GetActorLocation(), spawnerLocation);

            if (temp < minusDistance)
            {
                minusDistance = temp;
                firstWaypoint = Cast<ATDPathPoint>(iter);
            }
        }
    }


    blackboard->SetValueAsObject(FName(TEXT("WaypointActor")), firstWaypoint);
    blackboard->SetValueAsVector(FName(TEXT("WaypointPosition")), firstWaypoint->GetActorLocation());
    _enemyRef->TDSetPath(firstWaypoint);


    FVector spawnerPos = GetActorLocation();
    spawnerPos.Z += _enemyRef->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
    _enemyRef->SetActorLocation(spawnerPos);
}
