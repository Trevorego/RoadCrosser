// Fill out your copyright notice in the Description page of Project Settings.


#include "QueueLocation.h"

// Sets default values
AQueueLocation::AQueueLocation()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AQueueLocation::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AQueueLocation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

