// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "HeroAnimInstance.generated.h"

class UCharacterMovementComponent;
class AHeroBase;
class UPoseSearchDatabase;
struct FPoseSearchTrajectoryData;
struct FPoseSearchQueryTrajectory;
struct FPoseSearchTrajectory_WorldCollisionResults;

UCLASS()
class QUANTUMSKIRMISH_API UHeroAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	// Event Graph nodes
	void UpdateEssentialValues(float DeltaSeconds);
	void GenerateTrajectory(float DeltaSeconds);

private:
	// References
	UPROPERTY(BlueprintReadOnly, Category=Character, meta=(AllowPrivateAccess = true))
	AHeroBase* HeroCharacter;

	UPROPERTY(BlueprintReadOnly, Category=Movement, meta=(AllowPrivateAccess = true))
	UCharacterMovementComponent* CharacterMovement;

	// Essential values
	FTransform CharacterTransform;
	FTransform RootTransform;
	bool bHasAcceleration;
	FVector Acceleration;
	float AccelerationAmount;
	bool bHasVelocity;
	FVector Velocity;
	FVector VelocityLastFrame;
	FVector VelocityAcceleration;
	FVector LastNonZeroVelocity;
	float Speed2D;
	int32 MMDatabaseLOD;
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess = true))
	UPoseSearchDatabase* CurrentSelectedDatabase;
	TArray<FName> CurrentDatabaseTags;
	float HeavyLandSpeedThreshold;
	FTransform InteractionTransform;
	bool bOffsetRootBoneEnabled;

	// Trajectory
	FPoseSearchTrajectoryData* TrajectoryGenerationDataIdle;
	FPoseSearchTrajectoryData* TrajectoryGenerationDataMoving;
	FPoseSearchQueryTrajectory* Trajectory;
	float PreviousDesiredControllerYaw;
	FVector FutureVelocity;

public:
	bool IsMoving() const;
	bool IsStarting() const;
	
};
