// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonEnemyPawn.h"

#include "ToonPlayerPawn.h"
#include "Kismet/GameplayStatics.h"

AToonEnemyPawn::AToonEnemyPawn()
{
	FireRange = 1000.f;
	FireRate = 2.f;
	ProjectileDamage = 10.f;
}


void AToonEnemyPawn::BeginPlay()
{
	Super::BeginPlay();
	PlayerPawn = Cast<AToonPlayerPawn>(UGameplayStatics::GetPlayerPawn(this, 0));

	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &AToonEnemyPawn::CheckFireCondition, FireRate, true);
}


void AToonEnemyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(PlayerPawn)
	{
		TankPlayerLocation = PlayerPawn->GetActorLocation();
		DistanceToTank = FVector::Dist(GetActorLocation(), TankPlayerLocation);
	}
	else
	{
		PlayerPawn = Cast<AToonPlayerPawn>(UGameplayStatics::GetPlayerPawn(this, 0));
	}

	if (InFireRange())
	{
		RotateTurret(TankPlayerLocation);
	}
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

