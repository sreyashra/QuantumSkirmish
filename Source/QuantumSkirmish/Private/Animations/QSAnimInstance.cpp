// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/QSAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UQSAnimInstance::NativeInitializeAnimation()
{
	OwnerCharacter = Cast<ACharacter>(TryGetPawnOwner());
	if (OwnerCharacter)
	{
		OwnerMovementComponent = OwnerCharacter->GetCharacterMovement();
	}
}

void UQSAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if (OwnerCharacter)
	{
		Speed = OwnerCharacter->GetVelocity().Length();

		FRotator CurrentRotation = OwnerCharacter->GetActorRotation();
		FRotator CurrentRotationDelta = UKismetMathLibrary::NormalizedDeltaRotator(CurrentRotation, RotationLastFrame);
		RotationLastFrame = CurrentRotation;
		YawSpeed = CurrentRotationDelta.Yaw / DeltaSeconds;
		SmoothedYawSpeed = UKismetMathLibrary::FInterpTo(SmoothedYawSpeed, YawSpeed, DeltaSeconds, YawSpeedSmoothingFactor);

		if (OwnerMovementComponent)
		{
			bIsJumping = OwnerMovementComponent->IsFalling();
		}

		FRotator ControlRotation = OwnerCharacter->GetBaseAimRotation();
		LookRotationOffset = UKismetMathLibrary::NormalizedDeltaRotator(ControlRotation, CurrentRotation);
	}
}

void UQSAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{

}
