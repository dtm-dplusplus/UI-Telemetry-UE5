// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTankGameMode.h"

#include "Tank.h"
#include "Tower.h"
#include "TankPlayerController.h"
#include "GameFramework/PhysicsVolume.h"

#include "Kismet/GameplayStatics.h"

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
	HandleGameStart();
}

void AToonTankGameMode::HandleGameStart()
{
	// Count number of Towers in the world
	TargetTowers = GetTargetTowerCount();
	TankPlayer = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	TankPlayerController = Cast<ATankPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	StartGame();

	if(TankPlayerController)
	{
		TankPlayerController->SetPlayerEnbaledState(false);

		FTimerHandle playerEnableTimerHandle;
		const FTimerDelegate playerInputTimerDelegate = FTimerDelegate::CreateUObject(
			TankPlayerController, &ATankPlayerController::SetPlayerEnbaledState, true);
		GetWorldTimerManager().SetTimer(playerEnableTimerHandle, playerInputTimerDelegate, GameStartDelay, false);
	}

	
}

int32 AToonTankGameMode::GetTargetTowerCount() const
{
	TArray<AActor*> towers;
	UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), towers);

	return towers.Num();
}
 