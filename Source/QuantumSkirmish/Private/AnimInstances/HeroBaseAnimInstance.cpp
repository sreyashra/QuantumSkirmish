#include "AnimInstances/HeroBaseAnimInstance.h"
#include "Characters/HeroBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

DEFINE_LOG_CATEGORY(LogHeroBaseAnimInstance);

void UHeroBaseAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	APawn* Pawn = TryGetPawnOwner();
	if (!Pawn || !Pawn->IsValidLowLevel()) return;

	AHeroBase* Hero = Cast<AHeroBase>(Pawn);
	if (!Hero) return;

	FVector Velocity = Hero->GetVelocity();
	Velocity.Z = 0;
	Speed = Velocity.Size();

	if (UCharacterMovementComponent* MovementComponent = Hero->GetCharacterMovement())
	{
		bIsInAir = MovementComponent->IsFalling();

		FVector Acceleration = MovementComponent->GetCurrentAcceleration();
		bIsAccelerating = !Acceleration.IsNearlyZero() && (FVector::DotProduct(Acceleration.GetSafeNormal(), Velocity.GetSafeNormal()) > 0.1f);
	}

	FRotator ActorRotation = Hero->GetActorRotation();
	FRotator BaseAimRotation = Hero->GetBaseAimRotation();
	FRotator DeltaRPP = UKismetMathLibrary::NormalizedDeltaRotator(BaseAimRotation, ActorRotation);

	Roll = DeltaRPP.Roll;
	Pitch = DeltaRPP.Pitch;
	Yaw = DeltaRPP.Yaw;

	FRotator CurrentActorRotation = ActorRotation;
	FRotator DeltaYawRotation = UKismetMathLibrary::NormalizedDeltaRotator(RotationLastTick, CurrentActorRotation);
	float RawYawDiff = DeltaYawRotation.Yaw;
	float TargetYawDelta = RawYawDiff/7.f;

	YawDelta = FMath::FInterpTo(YawDelta, TargetYawDelta, DeltaTime, 6.f);

	RotationLastTick = ActorRotation;

	float FullBodyCurveValue = GetCurveValue(FName("FullBody"));
	bIsFullBody = FullBodyCurveValue > 0.f;
}

void UHeroBaseAnimInstance::PlayFireMontage()
{
	if (FireMontage && !Montage_IsPlaying(FireMontage))
	{
		Montage_Play(FireMontage);
	}
}
