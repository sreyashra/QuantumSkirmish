// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "QSPlayerController.generated.h"

class AQSPlayerCharacter;

UCLASS()
class AQSPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	// Only called on the server.
	void OnPossess(APawn* NewPawn) override;

	// Only called on the client, also on the listen server.
	void AcknowledgePossession(APawn* NewPawn) override;

private:
	UPROPERTY()
	AQSPlayerCharacter* QSPlayerCharacter;
	
};
