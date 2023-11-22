// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTankGameMode.h"

#include "ReplayGameInstance.h"
#include "ReplayPlayerController.h"
#include "Tank.h"
#include "Tower.h"
#include "TankPlayerController.h"

#include "Kismet/GameplayStatics.h"
#include "Windows/WindowsPlatformCrashContext.h"

void AToonTankGameMode::ActorDied(AActor* DeadActor)
{
	if(DeadActor == TankPlayer)
	{
		TankPlayer->HandleDestruction();
		TankPlayerController->SetPlayerEnbaledState(false);
		GameOver(false);
	}
	else if (ATower* deadTower = Cast<ATower>(DeadActor))
	{
		deadTower->HandleDestruction();
		TargetTowers--;
		if(TargetTowers == 0)
		{
			GameOver(true);
		}
	}
}

void AToonTankGameMode::BeginPlay()
{
	Super::BeginPlay();

	StartGame();

	// BP Event for designers. Start Game start timer. Adds UI widgets to viewport
	ReceiveStartGame();
}

void AToonTankGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	FPlatformCrashContext::SetGameData(TEXT("GameMode"), FString());
}

int32 AToonTankGameMode::GetTargetTowerCount() const
{
	TArray<AActor*> towers;
	UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), towers);

	return towers.Num();
}

void AToonTankGameMode::StartGame()
{
	// Adds game data to crash context
	FPlatformCrashContext::SetGameData(TEXT("GameMode"), TEXT("ToonTankGameMode"));

	// Get game instance
	if (bRecordGameplay)
	{
		if (ReplayGameInstance = Cast<UReplayGameInstance>(GetGameInstance()); ReplayGameInstance)
		{
			ReplayGameInstance->StartRecording();


		}
	}

	// Count number of Towers in the world
	TargetTowers = GetTargetTowerCount();

	// Get tank player and controller
	TankPlayer = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	TankPlayerController = Cast<ATankPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	if (TankPlayerController)
	{
		if (bGameStartDelay)
		{
			TankPlayerController->SetPlayerEnbaledState(false);

			// Set timer before enabling player input
			FTimerHandle playerEnableTimerHandle;
			const FTimerDelegate playerInputTimerDelegate = FTimerDelegate::CreateUObject(
				TankPlayerController,
				&ATankPlayerController::SetPlayerEnbaledState,
				true);

			GetWorldTimerManager().SetTimer(playerEnableTimerHandle, playerInputTimerDelegate, GameStartDelay, false);
		}
		else
		{
			TankPlayerController->SetPlayerEnbaledState(true);
		}
	}
}

void AToonTankGameMode::GameOver(const bool bWonGame)
{
	if (ReplayGameInstance && bRecordGameplay)
	{
		if(ReplayGameInstance->GetStopRecordingDelay())
		{
			// Set timer before enabling player input
			FTimerHandle stopRecordingTimerHandle; 
			const FTimerDelegate stopRecordingTimerDelegate = FTimerDelegate::CreateUObject(ReplayGameInstance,&UReplayGameInstance::StopRecording);
			GetWorldTimerManager().SetTimer(stopRecordingTimerHandle, stopRecordingTimerDelegate, ReplayGameInstance->GetStopRecordingDelayTime(),false);
		}
		else
		{
			ReplayGameInstance->StopRecording();
		}
	}

	// BP Event for designers. 
	RecieveGameOver(bWonGame);

	// ReplayPlayerController = Cast<AReplayPlayerController>(GetGameInstance()->ReplaySpectatorPlayerControllerClass);
	// if (ReplayPlayerController) { UE_LOG(LogTemp, Warning, TEXT("ReplayPlayerController is valid")); }
	// else UE_LOG(LogTemp, Warning, TEXT("ReplayPlayerController is NOT valid"));
}
 