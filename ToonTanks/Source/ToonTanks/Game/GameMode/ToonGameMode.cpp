// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonGameMode.h"

#include "../Pawn/ToonEnemyPawn.h"
#include "../Pawn/ToonPlayerPawn.h"
#include "Kismet/GameplayStatics.h"
#include "Windows/WindowsPlatformCrashContext.h"
#include "ToonTanks/Player/ToonPlayerController.h"

void AToonGameMode::ActorDied(AActor* DeadActor)
{
	// Destory the actor and notifty blueprint of the actor type for game state logic
	if (AToonEnemyPawn* DeadTower = Cast<AToonEnemyPawn>(DeadActor))
	{
		DeadTower->OnDestroy();
		EnemiesAliveCount--;
		BP_ActorDied(false);
	}
	else if (DeadActor == PlayerPawn)
	{
		PlayerPawn->OnDestroy();
		BP_ActorDied(true);
	}
}

void AToonGameMode::BeginPlay()
{
	Super::BeginPlay();

	// Adds game data to crash context
	FPlatformCrashContext::SetGameData(TEXT("GameMode"), TEXT("ToonGameMode"));

	EnemiesAliveCount = GetEnemiesAliveCount();

	// // Get tank player and controller
	PlayerPawn = Cast<AToonPlayerPawn>(UGameplayStatics::GetPlayerPawn(this, 0));
	PlayerController = Cast<AToonPlayerController>(UGameplayStatics::GetPlayerController(this, 0));


	// BP implementable event
	BP_GameStart();
}

void AToonGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	FPlatformCrashContext::SetGameData(TEXT("GameMode"), FString());
}

int32 AToonGameMode::GetEnemiesAliveCount() const
{
	TArray<AActor*> Towers;
	UGameplayStatics::GetAllActorsOfClass(this, AToonEnemyPawn::StaticClass(), Towers);

	return Towers.Num();
}