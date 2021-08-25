// Fill out your copyright notice in the Description page of Project Settings.


#include "Car.h"
#include "CosmicRoad/MovingCars.h"
#include "Engine/TriggerBox.h"
#include "CosmicRoad/Idiot.h"
#include "CosmicRoad/MyPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
ACar::ACar()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	RootComponent = BaseMesh;
}

// Called when the game starts or when spawned
void ACar::BeginPlay()
{
	Super::BeginPlay();
	
	Cast<UStaticMeshComponent>(GetDefaultSubobjectByName(TEXT("Base Mesh")))->OnComponentHit.AddDynamic(this, &ACar::OnHit);
}

// Called every frame
void ACar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PressurePlate)
		PressurePlate->OnActorBeginOverlap.AddDynamic(this, &ACar::KickOut);

	if (GetActorLocation().Y > 7617 && andac)
	{
		UKismetSystemLibrary::LaunchURL(TEXT("https://www.youtube.com/watch?v=eBGIQ7ZuuiU"));
		andac = false;
	}
}

// Called to bind functionality to input
void ACar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Forward", this, &ACar::MoveForward);
	PlayerInputComponent->BindAxis("Right", this, &ACar::MoveRight);
}

void ACar::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) 
{
	if (!Cast<AMovingCars>(OtherActor))
		return;

	if (ImpactSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSound, Hit.Location);
		ImpactSound = nullptr;
	}

	if (Cast<AMyPlayerController>(GetController()))
		Cast<AMyPlayerController>(GetController())->EndGame();

	DetachFromControllerPendingDestroy();
	UE_LOG(LogTemp, Warning, TEXT("CRASHED"));
}

void ACar::KickOut(class AActor* OverlappedActor, class AActor* OtherActor) 
{
	if (OtherActor == this && bIsCarry)
	{
		bIsCarry = false;
		FActorSpawnParameters SpawnInfo; 
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		FVector SpawnLocation = GetActorLocation();
		SpawnLocation.X += 150;
		GetWorld()->SpawnActor<AIdiot>(ClassToSpawn, SpawnLocation, GetActorRotation(), SpawnInfo);
		UE_LOG(LogTemp, Warning, TEXT("andac"));
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), SpawnSound, GetActorLocation());
	}
}

void ACar::MoveForward(float Value) 
{
	AddActorWorldOffset(FVector(0, Speed * Value * GetWorld()->GetDeltaSeconds(), 0), true);
}

void ACar::MoveRight(float Value) 
{
	AddActorWorldOffset(FVector(Speed * Value * GetWorld()->GetDeltaSeconds(), 0, 0), true);
}

