#include "Player/HeroPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Characters/HeroBase.h" // For referencing AHeroBase

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

	UEnhancedInputComponent* EnhancedInput = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInput->BindAction(MoveAction,  ETriggerEvent::Triggered, this, &AHeroPlayerController::Input_Move);
	EnhancedInput->BindAction(LookAction,  ETriggerEvent::Triggered, this, &AHeroPlayerController::Input_Look);
	EnhancedInput->BindAction(JumpAction,  ETriggerEvent::Started,   this, &AHeroPlayerController::Input_Jump);
	EnhancedInput->BindAction(CrouchAction,ETriggerEvent::Triggered, this, &AHeroPlayerController::Input_Crouch);
}

//////////////////////////////////////////////////////////////////////////
// Enhanced Input Event Handlers

void AHeroPlayerController::Input_Move(const FInputActionValue& Value)
{
	if (!bPawnAlive) return;
	if (AHeroBase* Hero = Cast<AHeroBase>(GetPawn()))
	{
		const FVector2D InputAxisVector = Value.Get<FVector2D>();
		Hero->HandleMovement(InputAxisVector);
	}
}

void AHeroPlayerController::Input_Look(const FInputActionValue& Value)
{
	if (!bPawnAlive) return;
	if (AHeroBase* Hero = Cast<AHeroBase>(GetPawn()))
	{
		const FVector2D InputAxisVector = Value.Get<FVector2D>();
		Hero->HandleLook(InputAxisVector);
	}
}

void AHeroPlayerController::Input_Jump()
{
	if (!bPawnAlive) return;
	if (AHeroBase* Hero = Cast<AHeroBase>(GetPawn()))
	{
		Hero->HandleJumpPressed();
	}
}

void AHeroPlayerController::Input_Crouch()
{
	if (!bPawnAlive) return;
	if (AHeroBase* Hero = Cast<AHeroBase>(GetPawn()))
	{
		Hero->HandleCrouchToggle();
	}
}
