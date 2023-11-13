// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "InputAction.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

ATank::ATank()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 4.f;
	SpringArm->CameraRotationLagSpeed = 4.f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	MovementSpeed = 300.0f;
	TurnSpeed = 150.0f;
	LookSpeed = 50.0f;
	bAlive = false;
}

void ATank::BeginPlay()
{
	ABasePawn::BeginPlay();

	bAlive = true;
}

void ATank::Tick(float DeltaTime)
{
	Super::BeginPlay();
}


// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent); //Call the parent version

	// Get the player controller
	TankPlayerController = Cast<APlayerController>(GetController());

	// Get the local player enhanced input subsystem
	const auto eiSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(TankPlayerController->GetLocalPlayer());
	//Add the input mapping context
	eiSubsystem->AddMappingContext(InputMapping, 0);

	// Get the EnhancedInputComponent
	const auto playerEIcomponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	//Bind to the mapping
	playerEIcomponent->BindAction(InputLook, ETriggerEvent::Triggered, this, &ATank::Look);
	playerEIcomponent->BindAction(InputMoveForward, ETriggerEvent::Triggered, this, &ATank::Move);
	playerEIcomponent->BindAction(InputTurn, ETriggerEvent::Triggered, this, &ATank::Turn);
	playerEIcomponent->BindAction(InputFire, ETriggerEvent::Triggered, this, &ATank::Fire);
}

void ATank::HandleDestruction()
{
	// Shake camera on death
	if (DeathCameraShakeClass)
		TankPlayerController->ClientStartCameraShake(DeathCameraShakeClass);

	Super::HandleDestruction();
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
	bAlive = false;
}

void ATank::Move(const FInputActionValue& Value)
{
	const float deltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
	const float deltaLocation = MovementSpeed * Value.Get<float>() * deltaTime;
	AddActorLocalOffset(FVector(deltaLocation, 0.0f, 0.0f));
}

void ATank::Turn(const FInputActionValue& Value)
{
	const float deltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
	const float deltaRotation = TurnSpeed * Value.Get<float>() * deltaTime;
	AddActorLocalRotation(FRotator(0.0f, deltaRotation, 0.0f), true);
}

void ATank::Look(const FInputActionValue& Value)
{
	FHitResult hitResult;
	TankPlayerController->GetHitResultUnderCursor(ECC_Visibility, false, hitResult);
	RotateTurret(hitResult.ImpactPoint);
}

void ATank::Fire()
{
	Super::Fire();

	if (LaunchCameraShakeClass)
		TankPlayerController->ClientStartCameraShake(LaunchCameraShakeClass);
}

