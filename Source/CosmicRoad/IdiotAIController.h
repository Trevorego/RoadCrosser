// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "IdiotAIController.generated.h"

/**
 * 
 */
UCLASS()
class COSMICROAD_API AIdiotAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	virtual void Tick(float DeltaSeconds) override;
	
protected:
	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn) override;

private:
	UPROPERTY(EditAnywhere)
	class UBehaviorTree* AIBehavior;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AQueueLocation> QueueClass;

	UPROPERTY(EditAnywhere)
	float YAxis = 1000;

	FVector PizzaLocation;
};
