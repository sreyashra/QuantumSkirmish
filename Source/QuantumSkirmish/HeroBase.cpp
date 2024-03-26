// Fill out your copyright notice in the Description page of Project Settings.


#include "HeroBase.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "ToughSword.h"

DEFINE_LOG_CATEGORY(LogHeroBaseCharacter);

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

	if (GetWorld())
	{
		// Setup spawn parameters
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		// Define the location and rotation for the new weapon
		FVector Location = GetActorLocation() + FVector(100, 0, 0); // Example offset
		FRotator Rotation = GetActorRotation();

		// Spawn the weapon
		AToughSword* NewWeapon = GetWorld()->SpawnActor<AToughSword>(ToughSwordClass, Location, Rotation, SpawnParams);

		if (NewWeapon)
		{
			// If the weapon has been successfully spawned, you can attach it to the player character
			// For example, attaching to a "WeaponSocket" on the character's mesh
			NewWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("ToughSwordAttachSocket"));

			// Additional logic after spawning (e.g., setting the weapon as the current weapon)
			// CurrentWeapon = NewWeapon; // Assuming you have a CurrentWeapon member variable
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

		//Sprinting
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &AHeroBase::StartSprint);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &AHeroBase::StopSprint);

		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
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
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		
		//Get right vector
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

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

void AHeroBase::StartSprint()
{
	GetCharacterMovement()->MaxWalkSpeed *= SprintSpeedMultiplier;
	
}

void AHeroBase::StopSprint()
{
	GetCharacterMovement()->MaxWalkSpeed /= SprintSpeedMultiplier;
	
}
