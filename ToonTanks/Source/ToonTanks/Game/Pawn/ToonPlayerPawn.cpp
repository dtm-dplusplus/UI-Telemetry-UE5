// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonPlayerPawn.h"

#include "Camera/CameraComponent.h"
#include "Camera/CameraShakeBase.h"
#include "GameFramework/SpringArmComponent.h"

#include "InputAction.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "../../Player/ToonPlayerController.h"

#include "ToonEnemyPawn.h"
#include "Engine/LocalPlayer.h"
#include "Kismet/GameplayStatics.h"

AToonPlayerPawn::AToonPlayerPawn()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 1.f;
	SpringArm->CameraRotationLagSpeed = 2.f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	//bAlive = true;

	MoveSpeed = 300.0f;
	TurnSpeed = 150.0f;
}

void AToonPlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Update Turret rotation based on mouse position
	RotateTurretOnLook();
}


// Called to bind functionality to input
void AToonPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent); //Call the parent version

	// Get the player controller
	PlayerController = Cast<AToonPlayerController>(GetController());

	// Get the local player enhanced input subsystem
	const auto EiSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	//Add the input mapping context
	EiSubsystem->AddMappingContext(InputMapping, 0);

	// Get the EnhancedInputComponent
	const auto PlayerEIcomponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	//Bind to the mapping
	PlayerEIcomponent->BindAction(InputMoveForward, ETriggerEvent::Triggered, this, &AToonPlayerPawn::MoveForward);
	PlayerEIcomponent->BindAction(InputTurn, ETriggerEvent::Triggered, this, &AToonPlayerPawn::RotateBase);
	PlayerEIcomponent->BindAction(InputFire, ETriggerEvent::Triggered, this, &AToonPlayerPawn::Fire);
}

void AToonPlayerPawn::OnDestroy()
{
	// Shake camera on death
	if (DeathCameraShakeClass) PlayerController->ClientStartCameraShake(DeathCameraShakeClass);

	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
	SetActorEnableCollision(false);

	// Notify Blueprint
	BP_Destroy();

	// We do this last so the code above executes ^^
	Super::OnDestroy();
}

void AToonPlayerPawn::MoveForward(const FInputActionValue& Value)
{
	const float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
	const float DeltaLocation = MoveSpeed * Value.Get<float>() * DeltaTime;
	AddActorLocalOffset(FVector(DeltaLocation, 0.0f, 0.0f));
}

void AToonPlayerPawn::RotateBase(const FInputActionValue& Value)
{
	const float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
	const float DeltaRotation = TurnSpeed * Value.Get<float>() * DeltaTime;
	AddActorLocalRotation(FRotator(0.0f, DeltaRotation, 0.0f), true);
}

void AToonPlayerPawn::RotateTurretOnLook()
{
	if (PlayerController)
	{
		FHitResult HitResult;
		PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
		RotateTurret(HitResult.ImpactPoint);
	}
}

void AToonPlayerPawn::Fire()
{
	Super::Fire();

	// Play camera shake
	if (LaunchCameraShakeClass)
	{
		PlayerController->ClientStartCameraShake(LaunchCameraShakeClass);
	}
}

