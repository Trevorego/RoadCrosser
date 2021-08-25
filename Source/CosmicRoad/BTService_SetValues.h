// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_SetValues.generated.h"

class AIdiot;
class AQueueLocation;
class ACar;

UCLASS(Blueprintable)
class COSMICROAD_API UBTService_SetValues : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTService_SetValues();

protected:
	virtual void TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds) override;

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<AIdiot> IdiotClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ACar> CarClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AQueueLocation> QueueClass;

	ACar* MyCar;
	AQueueLocation* QueueLocation;

};
