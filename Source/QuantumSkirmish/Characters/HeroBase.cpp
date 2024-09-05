// Fill out your copyright notice in the Description page of Project Settings.


#include "HeroBase.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

AHeroBase::AHeroBase()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AHeroBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AHeroBase::Move(const FInputActionValue& Value)
{
	
}

void AHeroBase::Look(const FInputActionValue& Value)
{
	
}

void AHeroBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHeroBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

