// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_SetValues.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"
#include "Idiot.h"
#include "QueueLocation.h"
#include "Pawns/Car.h"
#include "AIController.h"
#include "BrainComponent.h"


UBTService_SetValues::UBTService_SetValues() 
{
    NodeName = "Set Values";
}

void UBTService_SetValues::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds) 
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    for (auto i : TActorRange<ACar>(GetWorld(), CarClass))
    {
        MyCar = Cast<ACar>(i);
        break;
    }

    for (auto i : TActorRange<AQueueLocation>(GetWorld(), QueueClass))
    {
        QueueLocation = Cast<AQueueLocation>(i);
        break;
    }

    int32 Counter = 0;
    TArray<AIdiot*> Idiots;
    bool bIsFirst = false;
    for (auto i : TActorRange<AIdiot>(GetWorld(), IdiotClass))
    {
        if (i->GetActorLocation().Y > 1000)
            continue;

        Counter++;
        Idiots.Add(Cast<AIdiot>(i));
        if (Cast<AIdiot>(i) == Cast<AIdiot>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(GetSelectedBlackboardKey())))
        {
            if (Counter == 1)
            {
                OwnerComp.GetBlackboardComponent()->ClearValue("QueueNext");

                FVector QueuesLocation;
                QueuesLocation = QueueLocation->GetActorLocation();
                OwnerComp.GetBlackboardComponent()->SetValueAsVector("QueueLocation", QueuesLocation);
                bIsFirst = true;
            }
            else
            {
                FVector QueueNext = Idiots[Counter-2]->GetActorLocation();
                OwnerComp.GetBlackboardComponent()->SetValueAsVector("QueueNext", QueueNext);

                FVector QueuesLocation;
                QueuesLocation = QueueLocation->GetActorLocation();
                QueuesLocation.Y -= 220 * (Counter-1);
                OwnerComp.GetBlackboardComponent()->SetValueAsVector("QueueLocation", QueuesLocation);
            }
        }
    }

    if (!MyCar)
        return;

    OwnerComp.GetBlackboardComponent()->SetValueAsVector("CarLocation", MyCar->GetActorLocation());

    //UE_LOG(LogTemp, Warning, TEXT("%f"), FVector::Distance(MyCar->GetActorLocation(), Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(GetSelectedBlackboardKey()))->GetActorLocation()));
    if (FVector::Distance(MyCar->GetActorLocation(), Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(GetSelectedBlackboardKey()))->GetActorLocation()) <= 380 && !Cast<ACar>(MyCar)->bIsCarry && bIsFirst == true)
    {
        Cast<ACar>(MyCar)->bIsCarry = true;
        OwnerComp.GetBlackboardComponent()->SetValueAsBool("IsNearCar", true);
    }
    
}
