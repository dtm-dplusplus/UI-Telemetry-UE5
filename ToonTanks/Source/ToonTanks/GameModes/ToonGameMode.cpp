// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonGameMode.h"

// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "ToonTanks/Character/ToonTankPawn.h"
#include "ToonTanks/Character/ToonTowerPawn.h"
#include "Windows/WindowsPlatformCrashContext.h"
#include "ToonTanks/Player/ToonPlayerController.h"

AToonGameMode::AToonGameMode()
{
	PlayerControllerClass = AToonPlayerController::StaticClass();
	ReplaySpectatorPlayerControllerClass = AToonReplayPlayerController::StaticClass();
	DefaultPawnClass = AToonTankPawn::StaticClass();
}

void AToonGameMode::ActorDied(AActor* DeadActor)
{
	if (DeadActor == PlayerTank)
	{
		PlayerTank->OnDestroy();
		GameOver(false);
	}
	else if (AToonTowerPawn* deadTower = Cast<AToonTowerPawn>(DeadActor))
	{
		deadTower->OnDestroy();
		TargetTowers--;
		if (TargetTowers == 0)
		{
			GameOver(true);
		}
	}
}

void AToonGameMode::BeginPlay()
{
	Super::BeginPlay();

	StartGame();

	// BP Event for designers. Start Game start timer. Adds UI widgets to viewport
	ReceiveStartGame();
}

void AToonGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// Super::EndPlay(EndPlayReason);

	FPlatformCrashContext::SetGameData(TEXT("GameMode"), FString());
}

int32 AToonGameMode::GetTargetTowerCount() const
{
	TArray<AActor*> towers;
	UGameplayStatics::GetAllActorsOfClass(this, AToonTowerPawn::StaticClass(), towers);

	return towers.Num();
}

void AToonGameMode::StartGame()
{
	// Adds game data to crash context
	FPlatformCrashContext::SetGameData(TEXT("GameMode"), TEXT("ToonTankGameMode"));

	TargetTowers = GetTargetTowerCount();

	// // Get tank player and controller
	PlayerTank = Cast<AToonTankPawn>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void AToonGameMode::GameOver(const bool bWonGame)
{
	// BP Event for designers. 
	RecieveGameOver(bWonGame);
}
