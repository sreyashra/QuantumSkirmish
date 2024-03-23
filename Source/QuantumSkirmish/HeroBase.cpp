// Fill out your copyright notice in the Description page of Project Settings.


#include "HeroBase.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

// Sets default values
AHeroBase::AHeroBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create a camera boom
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bUsePawnControlRotation = true;

	//Create a folow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	//Don't rotate when the controler rotates. Let that just affect the camera
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	//Configure character movement
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f); //at this rotation rate
	GetCharacterMovement()->bOrientRotationToMovement = true; //Character moves in the direction of input (!!! Set this to false for ranged characters for aiming !!!)

}

// Called when the game starts or when spawned
void AHeroBase::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = Cast<APlayerController>(GetController());
	
	//Add Input Mapping Context
	if (PlayerController)
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(PlayerMappingContext, 0);
		}
	}
}

// Called every frame
void AHeroBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AHeroBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	//Setup action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AHeroBase::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AHeroBase::Look);
	}

}

void AHeroBase::Move(const FInputActionValue& Value)
{
	//Input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (PlayerController)
	{
		//Find out which way is forward
		const FRotator Rotation = PlayerController->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		//Get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		
		//Get right vector
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		//Add movement
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AHeroBase::Look(const FInputActionValue& Value)
{
	//Input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (PlayerController)
	{
		//Add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}
