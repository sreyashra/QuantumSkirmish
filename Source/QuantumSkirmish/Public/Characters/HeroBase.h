// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "HeroBase.generated.h"

class USkeletalMeshComponent;
class USpringArmComponent;
class UCameraComponent;


DECLARE_LOG_CATEGORY_EXTERN(LogHeroBase, Log, All);

UCLASS()
class QUANTUMSKIRMISH_API AHeroBase : public ACharacter
{
	GENERATED_BODY()

public:
	AHeroBase();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Mesh, meta=(AllowPrivateAccess = true))
	TObjectPtr<USkeletalMeshComponent> Mesh1P;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Camera, meta=(AllowPrivateAccess = true))
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Camera, meta=(AllowPrivateAccess = true))
	TObjectPtr<UCameraComponent> FirstPersonCamera;

public:
	TObjectPtr<USkeletalMeshComponent> GetMesh1P() const { return Mesh1P; }

	TObjectPtr<UCameraComponent> GetFirstPersonCamera() const { return FirstPersonCamera; }
	
};
