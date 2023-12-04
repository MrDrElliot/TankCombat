// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameplayAbilities/Public/AbilitySystemInterface.h"
#include "TankCharacter.generated.h"

class UTankAbilitySystemComponent;

UCLASS()
class TANKCOMBAT_API ATankCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATankCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	//~Begin IAbilitySystemInterface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	//~End IAbilitySystemInterface

	//VARIABLES

	FVector TargetLocation;
	bool bUpdateTurretRotation;
	
	UPROPERTY(Replicated)
	FRotator TurretRotation;
	
	UPROPERTY(Replicated, BlueprintReadOnly, EditAnywhere)
	float TurretRotationRate;

	
	//FUNCTIONS
	FRotator CalculateTurretRotation();

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void OnRep_PlayerState() override;
	virtual void PossessedBy(AController* NewController) override;
	
	
	UFUNCTION(BlueprintPure, meta = (BlueprintThreadSafe))
	FRotator GetTurretRotation() const { return TurretRotation; }

	UFUNCTION(BlueprintPure, meta = (BlueprintThreadSafe))
	FVector GetTurretTargetLocation() const { return TargetLocation; }


	//VARIABLES
	TWeakObjectPtr<UTankAbilitySystemComponent> AbilitySystemComponent;

	//RPC

	UFUNCTION(Server, Unreliable)
	void Server_SetTurretRotationRate(float NewRate);

	UFUNCTION(Server, Unreliable)
	void Server_UpdateTurretRotation(FRotator InRot);
	
};
