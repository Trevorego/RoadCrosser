// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class COSMICROAD_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	float Score = 0;

	UFUNCTION(BlueprintCallable)
	void EndGame();
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> StartScreenClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> HUDClass;

	UPROPERTY(EditDefaultsOnly)
	UUserWidget *HUD;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> EndScreenClass;

	void HUDStart();

};