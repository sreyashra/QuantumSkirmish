// Fill out your copyright notice in the Description page of Project Settings.


#include "AttachWeaponNotify.h"
#include "HeroBase.h"
#include "BaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"

void UAttachWeaponNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	AHeroBase* Character = Cast<AHeroBase>(MeshComp->GetOwner());
	if (Character)
	{
		ABaseWeapon* CurrentWeapon = Character->GetCurrentWeapon();

		if (CurrentWeapon)
		{
			FName HandSocketName = Character->GetHandSocket();
			FName HolsterSocketName = Character->GetHolsterSocket();

			FName TargetSocketName = Character->GetIsWeaponInHand() ? HolsterSocketName : HandSocketName;

			CurrentWeapon->AttachToCharacter(Character, TargetSocketName);
		}
	}
}
