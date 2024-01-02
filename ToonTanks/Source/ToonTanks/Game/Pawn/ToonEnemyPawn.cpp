// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonEnemyPawn.h"

#include "ToonPlayerPawn.h"
#include "Kismet/GameplayStatics.h"

AToonEnemyPawn::AToonEnemyPawn()
{
	FireRange = 1000.f;
	FireRate = 2.f;
	ProjectileDamageAmount = 10.f;
}


void AToonEnemyPawn::BeginPlay()
{
	Super::BeginPlay();

	PlayerTank = Cast<AToonPlayerPawn>(UGameplayStatics::GetPlayerPawn(this, 0));

	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &AToonEnemyPawn::CheckFireCondition, FireRate, true);
}


void AToonEnemyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TankPlayerLocation = PlayerTank->GetActorLocation();
	DistanceToTank = FVector::Dist(GetActorLocation(), TankPlayerLocation);

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
	if (PlayerTank)
	{
		if (InFireRange())
		{
			Fire();
		}
	}
}

