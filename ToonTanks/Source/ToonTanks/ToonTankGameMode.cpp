// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTankGameMode.h"

#include "Tank.h"
#include "Tower.h"
#include "Kismet/GameplayStatics.h"

void AToonTankGameMode::ActorDied(AActor* DeadActor)
{
	if(DeadActor == TankPlayer)
	{
		TankPlayer->HandleDestruction();
		TankPlayer->DisableInput(TankController);
		TankController->bShowMouseCursor = false;
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
	TankController = Cast<APlayerController>(TankPlayer->GetTankController());

}
 