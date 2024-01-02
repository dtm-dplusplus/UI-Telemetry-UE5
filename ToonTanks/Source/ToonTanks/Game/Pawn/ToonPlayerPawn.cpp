// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonPlayerPawn.h"

// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "InputAction.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Kismet/GameplayStatics.h"

AToonPlayerPawn::AToonPlayerPawn()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 4.f;
	SpringArm->CameraRotationLagSpeed = 4.f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	//bAlive = true;

	MovementSpeed = 300.0f;
	TurnSpeed = 150.0f;
	LookSpeed = 50.0f;

	//ProjectileDamageAmount = 40.f;

}

void AToonPlayerPawn::BeginPlay()
{
	Super::BeginPlay();


}

void AToonPlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Look();
}


// Called to bind functionality to input
void AToonPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent); //Call the parent version

	// Get the player controller
	TankPlayerController = Cast<APlayerController>(GetController());
	TankPlayerController->SetInputMode(FInputModeGameAndUI());

	// Get the local player enhanced input subsystem
	const auto eiSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(TankPlayerController->GetLocalPlayer());
	//Add the input mapping context
	eiSubsystem->AddMappingContext(InputMapping, 0);

	// Get the EnhancedInputComponent
	const auto playerEIcomponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	//Bind to the mapping
	playerEIcomponent->BindAction(InputMoveForward, ETriggerEvent::Triggered, this, &AToonPlayerPawn::Move);
	playerEIcomponent->BindAction(InputTurn, ETriggerEvent::Triggered, this, &AToonPlayerPawn::Turn);
	playerEIcomponent->BindAction(InputFire, ETriggerEvent::Triggered, this, &AToonPlayerPawn::Fire);
}

void AToonPlayerPawn::OnDestroy()
{
	// Shake camera on death
	if (DeathCameraShakeClass)
	{
		TankPlayerController->ClientStartCameraShake(DeathCameraShakeClass);
	}

	//Super::OnDestroy();
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
	bAlive = false;
}

void AToonPlayerPawn::Move(const FInputActionValue& Value)
{
	const float deltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
	const float deltaLocation = MovementSpeed * Value.Get<float>() * deltaTime;
	AddActorLocalOffset(FVector(deltaLocation, 0.0f, 0.0f));
}

void AToonPlayerPawn::Turn(const FInputActionValue& Value)
{
	const float deltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
	const float deltaRotation = TurnSpeed * Value.Get<float>() * deltaTime;
	AddActorLocalRotation(FRotator(0.0f, deltaRotation, 0.0f), true);
}

void AToonPlayerPawn::Look()
{
	if (TankPlayerController)
	{
		FHitResult hitResult;
		TankPlayerController->GetHitResultUnderCursor(ECC_Visibility, false, hitResult);
		RotateTurret(hitResult.ImpactPoint);
	}
}

void AToonPlayerPawn::Fire()
{
	Super::Fire();

	if (LaunchCameraShakeClass)
	{
		TankPlayerController->ClientStartCameraShake(LaunchCameraShakeClass);
	}

}

