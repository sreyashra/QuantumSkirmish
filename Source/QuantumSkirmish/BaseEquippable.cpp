// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEquippable.h"
#include "GameFramework/Character.h"

// Sets default values
ABaseEquippable::ABaseEquippable()
{
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));

	RootComponent = StaticMeshComponent;
}

void ABaseEquippable::Equip(ACharacter* Character, FName SocketName)
{
	if (Character && !IsEquipped)
	{
		IsEquipped = true;

		OwningCharacter = Character;
		AttachToCharacter(Character, SocketName);


		SetActorHiddenInGame(false);
		SetActorEnableCollision(false);
	}
	
}

void ABaseEquippable::UnEquip()
{
	if (IsEquipped)
	{
		IsEquipped = false;
	}

	//Logic for unequipping, e.g., detaching from the character
	OwningCharacter = nullptr;
}

void ABaseEquippable::AttachToCharacter(ACharacter* Character, FName SocketName)
{
	if (Character)
	{
		// Attach this actor's root component to the character's skeletal mesh component at the specified socket
		USkeletalMeshComponent* CharacterMesh = Character->GetMesh();
		if (CharacterMesh)
		{
			const FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
			this->AttachToComponent(CharacterMesh, AttachmentRules, SocketName);
		}
	}
}

UPrimitiveComponent* ABaseEquippable::GetMeshComponent() const
{
	if (StaticMeshComponent && StaticMeshComponent->IsVisible())
	{
		return StaticMeshComponent;
	}
	else if (SkeletalMeshComponent && SkeletalMeshComponent->IsVisible())
	{
		return SkeletalMeshComponent;
	}

	return nullptr;
}
