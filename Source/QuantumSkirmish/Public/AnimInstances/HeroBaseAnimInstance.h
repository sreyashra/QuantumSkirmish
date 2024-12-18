#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "HeroBaseAnimInstance.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogHeroBaseAnimInstance, Log, All);

UCLASS(Abstract)
class QUANTUMSKIRMISH_API UHeroBaseAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeUpdateAnimation(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category=Combat)
	virtual void PlayFireMontage();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Montages)
	UAnimMontage* FireMontage;

private:
	// Movement variables (Replicated from the Character)
	UPROPERTY(BlueprintReadOnly, Category=Movement, meta=(AllowPrivateAccess=true))
	float Speed;

	UPROPERTY(BlueprintReadOnly, Category=Movement, meta=(AllowPrivateAccess=true))
	bool bIsInAir;

	UPROPERTY(BlueprintReadOnly, Category=Movement, meta=(AllowPrivateAccess=true))
	bool bIsCrouched;
	
};
