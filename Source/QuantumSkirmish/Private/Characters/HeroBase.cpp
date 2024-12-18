#include "Characters/HeroBase.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "HeroComponents/HeroAbilitySystemComponent.h"

DEFINE_LOG_CATEGORY(LogHeroBase);

AHeroBase::AHeroBase()
{
	PrimaryActorTick.bCanEverTick = true;

	// Networking
	bReplicates = true;
	ACharacter::SetReplicateMovement(true);
	bAlwaysRelevant = true;
	SetNetUpdateFrequency(100.f);
	SetMinNetUpdateFrequency(33.f);

	//Rotation Usage
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Create the camera boom
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller
	CameraBoom->bDoCollisionTest = true;

	// Create the follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Create Ability System Component
	AbilitySystemComponent = CreateDefaultSubobject<UHeroAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
}

void AHeroBase::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

void AHeroBase::BeginPlay()
{
	Super::BeginPlay();

	if (AbilitySystemComponent)
	{
		UE_LOG(LogTemp, Log, TEXT("AHeroBase: AbilitySystemComponent is valid!"));
	}

}

void AHeroBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//////////////////////////////////////////////////////////////////////////
// Input Handler Methods (Called from PlayerController)

void AHeroBase::HandleMovement(const FVector2D& InputAxis)
{
	// Convert input to 3D movement (Forward/Right)
	if (Controller == nullptr) return;

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection   = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDirection, InputAxis.Y);
	AddMovementInput(RightDirection, InputAxis.X);
}

void AHeroBase::HandleLook(const FVector2D& InputAxis)
{
	AddControllerYawInput(InputAxis.X);
	AddControllerPitchInput(InputAxis.Y);
}

void AHeroBase::HandleJumpPressed()
{
	Jump();
}

void AHeroBase::HandleCrouchToggle()
{
	if (!CanCrouch())
	{
		UnCrouch(); // or no-op if we can't crouch
	}
	else
	{
		Crouch();
	}
}
