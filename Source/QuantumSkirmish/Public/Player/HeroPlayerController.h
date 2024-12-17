#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "HeroPlayerController.generated.h"

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

	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnRep_PlayerState() override;
	
	UPROPERTY(BlueprintAssignable)
	FOnPlayerStateReplicated OnPlayerStateReplicated;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	// Input mapping / actions
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

	// You can add more input actions for "Aim", "Fire", "Ability1", etc.

	// Local state
	bool bPawnAlive;

private:
	// Enhanced Input callbacks
	void Input_Move(const FInputActionValue& Value);
	void Input_Look(const FInputActionValue& Value);
	void Input_Jump();
	void Input_Crouch();
};
