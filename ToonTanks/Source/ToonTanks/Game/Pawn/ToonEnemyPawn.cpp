// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonEnemyPawn.h"

#include "Kismet/GameplayStatics.h"

AToonEnemyPawn::AToonEnemyPawn()
{
	FireRange = 1000.f;
	FireRate = 2.f;
}


void AToonEnemyPawn::BeginPlay()
{
	Super::BeginPlay();
	PlayerPawn = Cast<APawn>(UGameplayStatics::GetPlayerPawn(this, 0));

	// If the player is in range and this coincides with the timer, EnemyPawn Fires
	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &AToonEnemyPawn::CheckFireCondition, FireRate, true);
}


void AToonEnemyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Get Player rotation
	if(PlayerPawn)
	{
		TankPlayerLocation = PlayerPawn->GetActorLocation();
		DistanceToTank = FVector::Dist(GetActorLocation(), TankPlayerLocation);
	}

	// Check in range
	if (InFireRange()) RotateTurret(TankPlayerLocation);
}

bool AToonEnemyPawn::InFireRange()
{
	return DistanceToTank <= FireRange ? true : false;
}

void AToonEnemyPawn::CheckFireCondition()
{
	if (PlayerPawn)
	{
		if (InFireRange())
		{
			Fire();
		}
	}
}

