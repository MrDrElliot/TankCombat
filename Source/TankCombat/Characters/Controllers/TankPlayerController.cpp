// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"

ATankPlayerController::ATankPlayerController()
{
		bShowMouseCursor = true;
}

void ATankPlayerController::AcknowledgePossession(APawn* P)
{
	Super::AcknowledgePossession(P);
}
