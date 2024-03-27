// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseEquippable.generated.h"

class ACharacter;
UCLASS()
class QUANTUMSKIRMISH_API ABaseEquippable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseEquippable();

	virtual void Equip(ACharacter* Character, FName SocketName);
	virtual void UnEquip();

	UFUNCTION(BlueprintCallable, Category = "Equippable")
	virtual void AttachToCharacter(ACharacter* Character, FName SocketName);

	UFUNCTION(BlueprintCallable, Category = "Equippable")
	UPrimitiveComponent* GetMeshComponent()const;

	// Getter for IsEquipped
	UFUNCTION(BlueprintCallable, Category = "Equippable")
	bool GetIsEquipped() const { return IsEquipped; }

	// Setter for IsEquipped
	UFUNCTION(BlueprintCallable, Category = "Equippable")
	void SetIsEquipped(bool bNewIsEquipped) { IsEquipped = bNewIsEquipped; }

protected:
	//Reference to the character that has this item equipped
	ACharacter* OwningCharacter = nullptr;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* SkeletalMeshComponent;

	bool IsEquipped;
	
};
