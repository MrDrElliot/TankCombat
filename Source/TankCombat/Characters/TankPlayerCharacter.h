// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TankCharacter.h"
#include "TankPlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class TANKCOMBAT_API ATankPlayerCharacter : public ATankCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATankPlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	float DesiredCameraZoom;

	void InterpCameraZoom() const;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UCameraComponent> Camera;

	UFUNCTION(BlueprintCallable)
	void UpdateZoom(float InZoom);
};
