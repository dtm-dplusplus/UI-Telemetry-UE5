// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonGameMode.h"

// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "ToonTanks/Character/ToonTankPawn.h"
#include "ToonTanks/Character/ToonTowerPawn.h"
#include "Windows/WindowsPlatformCrashContext.h"
#include "ToonTanks/Player/ToonPlayerController.h"

void AToonGameMode::ActorDied(AActor* DeadActor)
{
	if (AToonTowerPawn* deadTower = Cast<AToonTowerPawn>(DeadActor))
	{
		deadTower->OnDestroy();
		EnemiesAliveCount--;
		RecieveActorDied(false);

		if (EnemiesAliveCount == 0) GameOver(true);
	}
	else if (DeadActor == PlayerTank)
	{
		PlayerTank->OnDestroy();
		RecieveActorDied(false);
		TankPlayerController->SetPlayerEnbaledState(false);
		GameOver(false);
	}
	 
}

void AToonGameMode::BeginPlay()
{
	Super::BeginPlay();

	// Adds game data to crash context
	FPlatformCrashContext::SetGameData(TEXT("GameMode"), TEXT("ToonTankGameMode"));

	EnemiesAliveCount = GetEnemiesAliveCount();

	// // Get tank player and controller
	PlayerTank = Cast<AToonTankPawn>(UGameplayStatics::GetPlayerPawn(this, 0));
	TankPlayerController = Cast<AToonPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	// BP Event for designers. Start Game start timer. Adds UI widgets to viewport
	ReceiveStartGame();
}

void AToonGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// Super::EndPlay(EndPlayReason);

	FPlatformCrashContext::SetGameData(TEXT("GameMode"), FString());
}

int32 AToonGameMode::GetEnemiesAliveCount() const
{
	TArray<AActor*> towers;
	UGameplayStatics::GetAllActorsOfClass(this, AToonTowerPawn::StaticClass(), towers);

	return towers.Num();
}

void AToonGameMode::GameOver(const bool bWonGame)
{
	// BP Event for designers. 
	RecieveGameOver(bWonGame);
}