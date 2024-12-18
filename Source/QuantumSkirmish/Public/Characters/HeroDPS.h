#pragma once

#include "CoreMinimal.h"
#include "Characters/HeroBase.h"
#include "HeroDPS.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogHeroDPS, Log, All);

UCLASS()
class QUANTUMSKIRMISH_API AHeroDPS : public AHeroBase
{
	GENERATED_BODY()

public:
	AHeroDPS();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DPS)
	float DamageMultiplier;

private:
		
};
