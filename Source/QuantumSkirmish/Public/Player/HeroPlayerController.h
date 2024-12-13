// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "HeroPlayerController.generated.h"

class UInputComponent;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerStateReplicated);

DECLARE_LOG_CATEGORY_EXTERN(LogHeroPlayerController, Log, All);

UCLASS()
class QUANTUMSKIRMISH_API AHeroPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AHeroPlayerController();
	bool bPawnAlive;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnRep_PlayerState() override;

	UPROPERTY(BlueprintAssignable)
	FOnPlayerStateReplicated OnPlayerStateReplicated;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	

private:
	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> CrouchAction;

	void Input_Move(const FInputActionValue& Value);
	void Input_Look(const FInputActionValue& Value);
	void Input_Jump();
	void Input_Crouch();
	
};
