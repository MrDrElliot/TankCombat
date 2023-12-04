// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TANKCOMBAT_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	
	ATankPlayerController();

	virtual void AcknowledgePossession(APawn* P) override;
	
};
