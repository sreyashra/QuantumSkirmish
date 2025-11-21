// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/QSPlayerController.h"
#include "Player/QSPlayerCharacter.h"

void AQSPlayerController::OnPossess(APawn* NewPawn)
{
	Super::OnPossess(NewPawn);

	QSPlayerCharacter = Cast<AQSPlayerCharacter>(NewPawn);
	if (QSPlayerCharacter)
	{
		QSPlayerCharacter->ServerSideInit();
	}
}

void AQSPlayerController::AcknowledgePossession(APawn* NewPawn)
{
	Super::AcknowledgePossession(NewPawn);

	QSPlayerCharacter = Cast<AQSPlayerCharacter>(NewPawn);
	if (QSPlayerCharacter)
	{
		QSPlayerCharacter->ClientSideInit();
	}
}
