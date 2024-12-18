#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HeroBase.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UHeroAbilitySystemComponent;

DECLARE_LOG_CATEGORY_EXTERN(LogHeroBase, Log, All);

UCLASS(Abstract) // Abstract since this is a base class not meant to be placed directly
class QUANTUMSKIRMISH_API AHeroBase : public ACharacter
{
	GENERATED_BODY()

public:
	AHeroBase();

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void HandleMovement(const FVector2D& InputAxis);
	virtual void HandleLook(const FVector2D& InputAxis);
	virtual void HandleJumpPressed();  // Called when jump input triggers
	virtual void HandleCrouchToggle(); // Called when crouch input triggers

	/** For future expansion: Abilities, stats, etc. */

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	/**
	 * These "Handle" methods can be called by the PlayerController input logic.
	 * Child classes (Tank/DPS/Healer) can override them if they need specific behaviors.
	 */
	/** Shared camera boom (pulls in towards the character if there's a collision) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	UCameraComponent* FollowCamera;

	/** Ability System Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Abilities)
	UHeroAbilitySystemComponent* AbilitySystemComponent;

private:
	
	 
public:
	UFUNCTION(BlueprintCallable, Category = Abilities)
	UHeroAbilitySystemComponent* GetAbilitySystemComponent() const { return AbilitySystemComponent; }

};
