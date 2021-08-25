// Fill out your copyright notice in the Description page of Project Settings.


#include "IdiotAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "QueueLocation.h"
#include "EngineUtils.h"


void AIdiotAIController::BeginPlay() 
{
    Super::BeginPlay();
    
}

void AIdiotAIController::OnPossess(APawn* InPawn) 
{
    Super::OnPossess(InPawn);
    if (!AIBehavior)
        return;

    RunBehaviorTree(AIBehavior);

    UE_LOG(LogTemp, Warning, TEXT("ALLAHHHH"));

    if (InPawn->GetActorLocation().Y > YAxis)
    {
        for (auto i : TActorRange<AQueueLocation>(GetWorld(), QueueClass))
        {
            PizzaLocation = Cast<AQueueLocation>(i)->GetActorLocation();
            break;
        }
        GetBlackboardComponent()->SetValueAsVector(TEXT("WasSpawned"), PizzaLocation);
    }
}

void AIdiotAIController::Tick(float DeltaSeconds) 
{
    Super::Tick(DeltaSeconds);
}