// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/QSCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "GAS/QSAbilitySystemComponent.h"
#include "GAS/QSAttributeSet.h"

// Sets default values
AQSCharacter::AQSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	QSAbilitySystemComponent = CreateDefaultSubobject<UQSAbilitySystemComponent>(TEXT("QSAbility System Component"));
	QSAttributeSet = CreateDefaultSubobject<UQSAttributeSet>(TEXT("QSAttribute Set"));
}

void AQSCharacter::ServerSideInit()
{
	QSAbilitySystemComponent->InitAbilityActorInfo(this, this);
	QSAbilitySystemComponent->ApplyInitialEffects();
}

void AQSCharacter::ClientSideInit()
{
	QSAbilitySystemComponent->InitAbilityActorInfo(this, this);
}

// Called when the game starts or when spawned
void AQSCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AQSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AQSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UAbilitySystemComponent* AQSCharacter::GetAbilitySystemComponent() const
{
	return QSAbilitySystemComponent;
}

