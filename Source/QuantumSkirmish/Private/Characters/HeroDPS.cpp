#include "Characters/HeroDPS.h"

DEFINE_LOG_CATEGORY(LogHeroDPS);

AHeroDPS::AHeroDPS()
{
	DamageMultiplier = 1.25f;
}

void AHeroDPS::BeginPlay()
{
	Super::BeginPlay();
}
