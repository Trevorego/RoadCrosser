// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"

#include "Blueprint/UserWidget.h"


void AMyPlayerController::BeginPlay() 
{
    Super::BeginPlay();

    HUD = CreateWidget(this, StartScreenClass);
    if (HUD != nullptr)
    {
        HUD->AddToViewport();

        FTimerHandle TimerHandle;
        GetWorldTimerManager().SetTimer(TimerHandle, this, &AMyPlayerController::HUDStart, 3.f, false);
    }
}

void AMyPlayerController::HUDStart() 
{
    if (HUD != nullptr)
    {
        HUD->RemoveFromViewport();

        HUD = CreateWidget(this, HUDClass);

        HUD->AddToViewport();
    }
}

void AMyPlayerController::EndGame() 
{
    if (HUD != nullptr)
    {
        HUD->RemoveFromViewport();

        HUD = CreateWidget(this, EndScreenClass);

        HUD->AddToViewport();

        FTimerHandle TimerHandle;
        GetWorldTimerManager().SetTimer(TimerHandle, this, &APlayerController::RestartLevel, 10.f, false);
    }
}
