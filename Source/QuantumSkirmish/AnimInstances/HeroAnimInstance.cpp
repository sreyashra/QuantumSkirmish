// Fill out your copyright notice in the Description page of Project Settings.


#include "HeroAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PoseSearch/PoseSearchDatabase.h"
#include "PoseSearch/PoseSearchTrajectoryTypes.h"
#include "PoseSearch/PoseSearchTrajectoryLibrary.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetMathLibrary.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"
#include "QuantumSkirmish/Characters/HeroBase.h"

void UHeroAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	HeroCharacter = Cast<AHeroBase>(TryGetPawnOwner());
	if (HeroCharacter)
	{
		CharacterMovement = HeroCharacter->GetCharacterMovement();
	}
}

void UHeroAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (HeroCharacter == nullptr)
	{
		HeroCharacter = Cast<AHeroBase>(TryGetPawnOwner());
	}
	if (HeroCharacter == nullptr) return;

	UpdateEssentialValues(DeltaSeconds);
	GenerateTrajectory(DeltaSeconds);
	
}

void UHeroAnimInstance::UpdateEssentialValues(float DeltaSeconds)
{
	if (HeroCharacter == nullptr) return;

	CharacterTransform = HeroCharacter->GetActorTransform();

	// Get the console variable value to check if the root bone offset is enabled
	bOffsetRootBoneEnabled = IConsoleManager::Get().FindTConsoleVariableDataBool(TEXT("animnode.offsetrootbone_enable"))->GetValueOnGameThread();
	if (bOffsetRootBoneEnabled)
	{
		// Get the root bone transform from the skeletal mesh component's "root" socket
		RootTransform = HeroCharacter->GetMesh()->GetSocketTransform(TEXT("root"), RTS_World);

		// Modify the rotation (add 90 degrees to the yaw)
		FRotator RootRotation = RootTransform.GetRotation().Rotator();
		RootRotation.Yaw = 90.0f;

		// Set the modified rotation back into the RootTransform as a quaternion
		RootTransform.SetRotation(FQuat(RootRotation));
	}
	else
	{
		// If offset is not enabled, just use the character's transform
		RootTransform = CharacterTransform;
	}

	// Set the acceleration of the character
	Acceleration = CharacterMovement->GetCurrentAcceleration();
	AccelerationAmount = Acceleration.Length() / CharacterMovement->GetMaxAcceleration();
	bHasAcceleration = AccelerationAmount > 0.f ? true : false;

	//Set Velocity of character
	VelocityLastFrame = Velocity;
	Velocity = CharacterMovement->Velocity;
	Speed2D = Velocity.Size2D();
	
	FVector DeltaVelocity = Velocity - VelocityLastFrame;
	VelocityAcceleration = DeltaVelocity / FMath::Max(DeltaSeconds, 0.001f);

	bHasVelocity = !Velocity.IsNearlyZero();
	if (bHasVelocity)
	{
		LastNonZeroVelocity = Velocity;
	}

	MMDatabaseLOD = IConsoleManager::Get().FindTConsoleVariableDataInt(TEXT("DDCvar.MMDatabaseLOD"))->GetValueOnGameThread();

	if (CurrentSelectedDatabase != nullptr)
	{
		CurrentDatabaseTags = CurrentSelectedDatabase->Tags;
	}
}

void UHeroAnimInstance::GenerateTrajectory(float DeltaSeconds)
{
	// Select the appropriate trajectory generation data
	const FPoseSearchTrajectoryData* SelectedTrajectoryData = (Speed2D > 0.f) ? TrajectoryGenerationDataMoving : TrajectoryGenerationDataIdle;

	if (!SelectedTrajectoryData) return;

	FPoseSearchQueryTrajectory InOutTrajectory;
	FPoseSearchQueryTrajectory OutTrajectory;

	FPoseSearchQueryTrajectorySample Sample;
	Sample.Position = HeroCharacter->GetActorLocation();
	Sample.Facing = HeroCharacter->GetActorRotation().Quaternion();
	Sample.AccumulatedSeconds = 0.f;

	InOutTrajectory.Samples.Add(Sample);

	float InOutDesiredControllerYawLastUpdate = PreviousDesiredControllerYaw;
	PreviousDesiredControllerYaw = HeroCharacter->GetControlRotation().Yaw;
	
	UPoseSearchTrajectoryLibrary::PoseSearchGenerateTrajectory(this, *SelectedTrajectoryData,
		DeltaSeconds, InOutTrajectory, InOutDesiredControllerYawLastUpdate, OutTrajectory);

	FPoseSearchTrajectory_WorldCollisionResults CollisionResults;
	TArray<AActor*> ActorsToIgnore;
	UPoseSearchTrajectoryLibrary::HandleTrajectoryWorldCollisions(this, this, OutTrajectory,
		true, 0.01f, OutTrajectory, CollisionResults, TraceTypeQuery1,
		false, ActorsToIgnore, EDrawDebugTrace::None);

	Trajectory = &OutTrajectory;

	FPoseSearchQueryTrajectorySample TrajectorySample0_5 = OutTrajectory.GetSampleAtTime(0.5f);
	FPoseSearchQueryTrajectorySample TrajectorySample0_4 = OutTrajectory.GetSampleAtTime(0.4f);

	FutureVelocity = (TrajectorySample0_5.Position - TrajectorySample0_4.Position) * 10.f;
}

EOffsetRootRotationMode UHeroAnimInstance::GetOffsetRootRotationMode() const
{
	if (IsAnyMontagePlaying() && GetActiveSlotMontageInstanceByName(FName("DefaultSlot")) != nullptr)
}

bool UHeroAnimInstance::IsMoving() const
{
	constexpr float Tolerance = 0.1f;

	bool bIsCurrentVelocityZero = FMath::IsNearlyZero(Velocity.X, Tolerance) && FMath::IsNearlyZero(Velocity.Y, Tolerance);
	bool bIsFuturevelocityZero = FMath::IsNearlyZero(FutureVelocity.X, Tolerance) && FMath::IsNearlyZero(FutureVelocity.Y, Tolerance);

	return bIsCurrentVelocityZero && bIsFuturevelocityZero;
}

bool UHeroAnimInstance::IsStarting() const
{
	constexpr float VelocityThreshold = 100.f;

	float FutureVelocityLength = FVector(FutureVelocity.X, FutureVelocity.Y, 0.f).Size();
	float CurrentVelocityLength = FVector(Velocity.X, Velocity.Y, 0.f).Size();

	bool bIsVelocityGreater = (FutureVelocityLength >= CurrentVelocityLength + VelocityThreshold);
	bool bIsNotPivot = !CurrentDatabaseTags.Contains("Pivots");
	bool bIsMoving = IsMoving();

	return bIsVelocityGreater && bIsNotPivot && bIsMoving;
}

bool UHeroAnimInstance::IsPivoting(ERotationMode RotationMode)
{
	FRotator FutureRotation = UKismetMathLibrary::MakeRotFromX(FutureVelocity);
	FRotator CurrentRotation = UKismetMathLibrary::MakeRotFromX(Velocity);

	float DeltaYaw = FMath::Abs(FutureRotation.Yaw - CurrentRotation.Yaw);
	float Threshold = (RotationMode == ERotationMode::OrientToMovement) ? 60.f : 40.f;
	return DeltaYaw >= Threshold;
}

bool UHeroAnimInstance::ShouldTurnInPlace()
{
	FRotator CharacterRotation = HeroCharacter->GetActorRotation();
	FRotator RootRotation = HeroCharacter->GetMesh()->GetComponentRotation();

	float DeltaYaw = FMath::Abs(CharacterRotation.Yaw - RootRotation.Yaw);

	if (DeltaYaw >= 50.f)
	{
		if (HeroCharacter->bWantsToAim || (HeroCharacter->MovementState == EMovementState::Idle && HeroCharacter->MovementStateLastFrame == EMovementStateLastFrame::Moving))
		{
			return true;
		}
	}

	return false;
}

bool UHeroAnimInstance::HasJustLandedLight()
{
	if (HeroCharacter->bJustLanded)
	{
		float LandVelocityZ = HeroCharacter->GetCharacterMovement()->Velocity.Z;
		if (FMath::Abs(LandVelocityZ) < HeavyLandSpeedThreshold)
		{
			return true;
		}
	}

	return false;
}

bool UHeroAnimInstance::HasJustLandedHeavy()
{
	if (HeroCharacter->bJustLanded)
	{
		float LandVelocityZ = HeroCharacter->GetCharacterMovement()->Velocity.Z;
		if (FMath::Abs(LandVelocityZ) >= HeavyLandSpeedThreshold)
		{
			return true;
		}
	}

	return false;
}

bool UHeroAnimInstance::ShouldSpinTransition()
{
	FRotator CharacterRotation = HeroCharacter->GetActorRotation();
	FRotator RootRotation = HeroCharacter->GetMesh()->GetComponentRotation();

	float DeltaYaw = FMath::Abs(FMath::FindDeltaAngleDegrees(CharacterRotation.Yaw, RootRotation.Yaw));

	if (DeltaYaw >= 130.f)
	{
		if (Speed2D >= 150.f)
		{
			if (!CurrentDatabaseTags.Contains(TEXT("Pivots")))
			{
				return true;
			}
		}
	}
	return false;
}

