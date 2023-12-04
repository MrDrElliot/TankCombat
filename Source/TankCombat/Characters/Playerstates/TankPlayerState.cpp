// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerState.h"

#include "TankCombat/AbilitySystem/TankAbilitySystemComponent.h"

ATankPlayerState::ATankPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UTankAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	NetUpdateFrequency = 1000.0f;
}
