// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/HeroDPS.h"
#include "HeroDPS_Revenant.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogHeroDPS_Revenant, Log, All);

UCLASS()
class QUANTUMSKIRMISH_API AHeroDPS_Revenant : public AHeroDPS
{
	GENERATED_BODY()

public:
	AHeroDPS_Revenant();

protected:
	virtual void BeginPlay() override;

private:
	
	
	
};
