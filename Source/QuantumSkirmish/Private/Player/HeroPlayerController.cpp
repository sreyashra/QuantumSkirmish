// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/HeroPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

DEFINE_LOG_CATEGORY(LogHeroPlayerController);


AHeroPlayerController::AHeroPlayerController()
{
	bReplicates = true;
	bPawnAlive = true;
}

void AHeroPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	bPawnAlive = true;
}

void AHeroPlayerController::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	OnPlayerStateReplicated.Broadcast();
}

void AHeroPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}
}

void AHeroPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AHeroPlayerController::Input_Move);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AHeroPlayerController::Input_Look);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AHeroPlayerController::Input_Jump);
	EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Triggered, this, &AHeroPlayerController::Input_Crouch);
}

void AHeroPlayerController::Input_Move(const FInputActionValue& Value)
{
	if (!bPawnAlive) return;

	const FVector2D InputAxisVector = Value.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

void AHeroPlayerController::Input_Look(const FInputActionValue& Value)
{
	const FVector2D InputAxisVector = Value.Get<FVector2D>();
	AddYawInput(InputAxisVector.X);
	AddPitchInput(InputAxisVector.Y);
}

void AHeroPlayerController::Input_Jump()
{
	
}

void AHeroPlayerController::Input_Crouch()
{
	
}
