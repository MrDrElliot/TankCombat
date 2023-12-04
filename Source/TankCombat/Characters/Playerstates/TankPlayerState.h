// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "TankCombat/AbilitySystem/TankAbilitySystemComponent.h"

#include "TankPlayerState.generated.h"

class UTankAttributeSet;
class UTankAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class TANKCOMBAT_API ATankPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	ATankPlayerState();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTankAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTankAttributeSet* TankAttributes;
};
