// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/QSAttributeSet.h"
#include "Net/UnrealNetwork.h"

void UQSAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(UQSAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UQSAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
}

void UQSAttributeSet::OnRep_Health(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UQSAttributeSet, Health, OldValue);
}

void UQSAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UQSAttributeSet, MaxHealth, OldValue);
}

void UQSAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UQSAttributeSet, Mana, OldValue);
}

void UQSAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UQSAttributeSet, MaxMana, OldValue);
}
