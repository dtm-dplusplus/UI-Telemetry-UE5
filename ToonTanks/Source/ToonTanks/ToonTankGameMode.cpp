// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTankGameMode.h"

#include "Tank.h"
#include "Tower.h"
#include "TankPlayerController.h"

#include "Kismet/GameplayStatics.h"

void AToonTankGameMode::ActorDied(AActor* DeadActor)
{
	if(DeadActor == TankPlayer)
	{
		TankPlayer->HandleDestruction();
		TankPlayerController->SetPlayerEnbaledState(false);
	}
	else if (ATower* deadTower = Cast<ATower>(DeadActor))
	{
		deadTower->HandleDestruction();
	}
}

void AToonTankGameMode::BeginPlay()
{
	Super::BeginPlay();

	TankPlayer = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	TankPlayerController = Cast<ATankPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

}
 