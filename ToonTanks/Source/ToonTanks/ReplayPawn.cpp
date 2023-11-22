// Fill out your copyright notice in the Description page of Project Settings.


#include "ReplayPawn.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "ReplayGameInstance.h"
#include "ReplayPlayerController.h"
#include "ToonTankGameMode.h"

AReplayPawn::AReplayPawn()
{
}

void AReplayPawn::BeginPlay()
{
	Super::BeginPlay();

	ReplayGameInstance = Cast<UReplayGameInstance>(GetGameInstance());
}

void AReplayPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Get the player controller
	AToonTankGameMode* GameMode = (AToonTankGameMode*)GetWorld()->GetAuthGameMode();
	ReplayPlayerController = Cast<AReplayPlayerController>(GameMode->ReplaySpectatorPlayerControllerClass->GetSuperClass());

	// Get the local player enhanced input subsystem
	const auto eiSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(ReplayPlayerController->GetLocalPlayer());
	//Add the input mapping context
	eiSubsystem->AddMappingContext(InputMappingContext, 0);

	// Get the EnhancedInputComponent
	const auto playerEIcomponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	//Bind to the mapping
	//playerEIcomponent->BindAction(InputToggleReplay, ETriggerEvent::Triggered, this, &AReplayPawn::ToggleReplay);
	playerEIcomponent->BindAction(InputRestartReplay, ETriggerEvent::Triggered, this, &AReplayPawn::RestartReplay);

}

//void AReplayPawn::ToggleReplay()
//{
//
//}

void AReplayPawn::RestartReplay()
{
	ReplayGameInstance->StartReplay();
}
