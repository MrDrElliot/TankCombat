// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"


// Sets default values
ATankPlayerCharacter::ATankPlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bInheritPitch = 0;
	SpringArmComponent->bInheritRoll = 0;
	SpringArmComponent->bInheritYaw = 0;


	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArmComponent, "SpringEndpoint");
}

// Called when the game starts or when spawned
void ATankPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if(IsLocallyControlled())
	{
		DesiredCameraZoom = SpringArmComponent->TargetArmLength;
	}
}

void ATankPlayerCharacter::InterpCameraZoom() const
{
	if(SpringArmComponent)
	{
		SpringArmComponent->TargetArmLength = FMath::FInterpConstantTo(SpringArmComponent->TargetArmLength, DesiredCameraZoom, GetWorld()->GetDeltaSeconds(), 400.0f);
	}
}

// Called every frame
void ATankPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	InterpCameraZoom();
}

// Called to bind functionality to input
void ATankPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ATankPlayerCharacter::UpdateZoom(const float InZoom)
{
	DesiredCameraZoom = DesiredCameraZoom + (FMath::Clamp(InZoom, -1, 1) * 200.0f);
}


