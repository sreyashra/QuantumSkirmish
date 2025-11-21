// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/QSAbilitySystemComponent.h"

void UQSAbilitySystemComponent::ApplyInitialEffects()
{
	if (!GetOwner() || !GetOwner()->HasAuthority()) return;
	

	for (const TSubclassOf<UGameplayEffect>& EffectClass : InitialEffects)
	{
		if (EffectClass)
		{
			FGameplayEffectContextHandle EffectContext = MakeEffectContext();
			EffectContext.AddSourceObject(this);
			FGameplayEffectSpecHandle NewHandle = MakeOutgoingSpec(EffectClass, 1, EffectContext);
			if (NewHandle.IsValid())
			{
				ApplyGameplayEffectSpecToSelf(*NewHandle.Data.Get());
			}
		}
	}
}
