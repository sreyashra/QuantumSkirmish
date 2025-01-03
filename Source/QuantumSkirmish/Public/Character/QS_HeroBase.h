// © 2025 KreypX. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "QS_HeroBase.generated.h"

UCLASS()
class QUANTUMSKIRMISH_API AQS_HeroBase : public ACharacter
{
	GENERATED_BODY()

public:
	AQS_HeroBase();

protected:
	virtual void BeginPlay() override;

};
