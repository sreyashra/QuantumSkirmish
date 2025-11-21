// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "QSCharacter.generated.h"

class UQSAbilitySystemComponent;
class UQSAttributeSet;

UCLASS()
class AQSCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AQSCharacter();

	void ServerSideInit();
	void ClientSideInit();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/***************************/
	/**** Gameplay Ability ****/
	/***************************/
public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

private:
	UPROPERTY(VisibleDefaultsOnly, Category = "Gamplay Ability")
	UQSAbilitySystemComponent* QSAbilitySystemComponent;

	UPROPERTY()
	UQSAttributeSet* QSAttributeSet;

};
