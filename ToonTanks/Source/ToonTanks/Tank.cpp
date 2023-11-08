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
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	MovementSpeed = 300.0f;
	TurnSpeed = 150.0f;
}

void ATank::BeginPlay()
{
	ABasePawn::BeginPlay();

}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent); //Call the parent version

	// Get the player controller
	auto playerController = Cast<APlayerController>(GetController());

	// Get the local player enhanced input subsystem
	auto eiSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer());
	//Add the input mapping context
	eiSubsystem->AddMappingContext(InputMapping, 0);

	// Get the EnhancedInputComponent
	auto playerEIcomponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	//Bind to the mapping
	playerEIcomponent->BindAction(InputMoveForward, ETriggerEvent::Triggered, this, &ATank::Move);
	playerEIcomponent->BindAction(InputTurn, ETriggerEvent::Triggered, this, &ATank::Turn);
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

