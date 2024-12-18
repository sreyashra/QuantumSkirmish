#include "AnimInstances/HeroBaseAnimInstance.h"
#include "Characters/HeroBase.h"
#include "GameFramework/CharacterMovementComponent.h"

DEFINE_LOG_CATEGORY(LogHeroBaseAnimInstance);


void UHeroBaseAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	APawn* Pawn = TryGetPawnOwner();
	if (!Pawn) return;

	AHeroBase* Hero = Cast<AHeroBase>(Pawn);
	if (Hero && Hero->IsValidLowLevel())
	{
		Speed = Hero->GetVelocity().Size2D();
		bIsInAir = Hero->GetMovementComponent()->IsFalling();
		bIsCrouched = Hero->GetMovementComponent()->IsCrouching();
	}
}

void UHeroBaseAnimInstance::PlayFireMontage()
{
	if (FireMontage && !Montage_IsPlaying(FireMontage))
	{
		Montage_Play(FireMontage);
	}
}
