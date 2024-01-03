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
	SpringArm->CameraLagSpeed = 4.f;
	SpringArm->CameraRotationLagSpeed = 4.f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	//bAlive = true;

	MoveSpeed = 300.0f;
	TurnSpeed = 150.0f;
	LookSpeed = 50.0f;

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
	PlayerController = Cast<AToonPlayerController>(GetController());

	// Get the local player enhanced input subsystem
	const auto EiSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	//Add the input mapping context
	EiSubsystem->AddMappingContext(InputMapping, 0);

	// Get the EnhancedInputComponent
	const auto PlayerEIcomponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	//Bind to the mapping
	PlayerEIcomponent->BindAction(InputMoveForward, ETriggerEvent::Triggered, this, &AToonPlayerPawn::Move);
	PlayerEIcomponent->BindAction(InputTurn, ETriggerEvent::Triggered, this, &AToonPlayerPawn::Turn);
	PlayerEIcomponent->BindAction(InputFire, ETriggerEvent::Triggered, this, &AToonPlayerPawn::Fire);
}

void AToonPlayerPawn::OnDestroy()
{

	// Disable input
	PlayerController->SetPlayerInputState(false);

	// Shake camera on death
	if (DeathCameraShakeClass)
	{
		PlayerController->ClientStartCameraShake(DeathCameraShakeClass);
	}

	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);

	// Notify Blueprint
	RecieveDestroy();

	Super::OnDestroy();
}

void AToonPlayerPawn::Move(const FInputActionValue& Value)
{
	const float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
	const float DeltaLocation = MoveSpeed * Value.Get<float>() * DeltaTime;
	AddActorLocalOffset(FVector(DeltaLocation, 0.0f, 0.0f));
}

void AToonPlayerPawn::Turn(const FInputActionValue& Value)
{
	const float deltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
	const float deltaRotation = TurnSpeed * Value.Get<float>() * deltaTime;
	AddActorLocalRotation(FRotator(0.0f, deltaRotation, 0.0f), true);
}

void AToonPlayerPawn::Look()
{
	if (PlayerController)
	{
		FHitResult hitResult;
		PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, hitResult);
		RotateTurret(hitResult.ImpactPoint);
	}
}

void AToonPlayerPawn::Fire()
{
	Super::Fire();

	if (LaunchCameraShakeClass)
	{
		PlayerController->ClientStartCameraShake(LaunchCameraShakeClass);
	}
}

