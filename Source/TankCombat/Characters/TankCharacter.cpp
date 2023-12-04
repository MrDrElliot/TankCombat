// Fill out your copyright notice in the Description page of Project Settings.


#include "TankCharacter.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Net/UnrealNetwork.h"
#include "Playerstates/TankPlayerState.h"
#include "TankCombat/AbilitySystem/TankAbilitySystemComponent.h"


class ATankPlayerState;
// Sets default values
ATankCharacter::ATankCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TurretRotationRate = 10.0f;
}

// Called when the game starts or when spawned
void ATankCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATankCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(ThisClass, TurretRotation, COND_SkipOwner);
}

UAbilitySystemComponent* ATankCharacter::GetAbilitySystemComponent() const
{
	if (const ATankPlayerState* PS = GetPlayerState<ATankPlayerState>())
	{
		return PS->AbilitySystemComponent;
	}
	return nullptr;
}

// Called every frame
void ATankCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(IsLocallyControlled())
	{
		FRotator CachedTurretRotation = TurretRotation;
		
		TurretRotation = FMath::RInterpConstantTo(TurretRotation, CalculateTurretRotation(), DeltaTime, TurretRotationRate);
		if(!HasAuthority())
		{
			Server_UpdateTurretRotation(TurretRotation);
		}
	}
}

// Called to bind functionality to input
void ATankCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ATankCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	if (ATankPlayerState* PS = GetPlayerState<ATankPlayerState>())
	{
		// Set the ASC for clients. Server does this in PossessedBy.
		AbilitySystemComponent = Cast<UTankAbilitySystemComponent>(PS->GetAbilitySystemComponent());

		// Init ASC Actor Info for clients. Server will init its ASC when it possesses a new Actor.
		AbilitySystemComponent->InitAbilityActorInfo(PS, this);
	}

}

void ATankCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (ATankPlayerState* PS = GetPlayerState<ATankPlayerState>())
	{
		// Set the ASC on the Server. Clients do this in OnRep_PlayerState()
		AbilitySystemComponent = Cast<UTankAbilitySystemComponent>(PS->GetAbilitySystemComponent());

		// AI won't have PlayerControllers so we can init again here just to be sure. No harm in initing twice for heroes that have PlayerControllers.
		PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS, this);
	}
	
}

void ATankCharacter::Server_SetTurretRotationRate_Implementation(const float NewRate)
{
	TurretRotationRate = NewRate;
}


FRotator ATankCharacter::CalculateTurretRotation()
{
	if(const APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0 ))
	{
		FHitResult HitResult;
		PC->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);


		
		TargetLocation = HitResult.Location;
		const FRotator LookAtRot = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetLocation);

		return FRotator(0, LookAtRot.Yaw, 0);
	}
	return FRotator::ZeroRotator;
}


void ATankCharacter::Server_UpdateTurretRotation_Implementation(const FRotator InRot)
{
	TurretRotation = InRot;
}