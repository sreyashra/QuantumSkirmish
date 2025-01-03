// © 2025 KreypX. All rights reserved.


#include "Player/QS_PlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

AQS_PlayerController::AQS_PlayerController()
{
	bReplicates = true;
	bPawnAlive = true;
}

void AQS_PlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	bPawnAlive = true;
}

void AQS_PlayerController::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	OnPlayerStateReplicated.Broadcast();
}

void AQS_PlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(DefaultMappingContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);

	Subsystem->AddMappingContext(DefaultMappingContext, 0);
}

void AQS_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AQS_PlayerController::Input_Move);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AQS_PlayerController::Input_Look);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AQS_PlayerController::Input_Jump);
}

void AQS_PlayerController::Input_Move(const FInputActionValue& Value)
{
	if (!bPawnAlive) return;
	const FVector2D InputAxisVector = Value.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.0f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

void AQS_PlayerController::Input_Look(const FInputActionValue& Value)
{
	const FVector2D InputAxisVector = Value.Get<FVector2D>();
	AddYawInput(InputAxisVector.X);
	AddPitchInput(InputAxisVector.Y);
}

void AQS_PlayerController::Input_Jump()
{
	if (!bPawnAlive) return;
}
