// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTowerPawn.h"

#include "ToonTankPawn.h"
#include "Kismet/GameplayStatics.h"

AToonTowerPawn::AToonTowerPawn()
{
	FireRange = 1000.f;
	FireRate = 2.f;
	ProjectileDamageAmount = 10.f;
}


void AToonTowerPawn::BeginPlay()
{
	 Super::BeginPlay();

	PlayerTank = Cast<AToonTankPawn>(UGameplayStatics::GetPlayerPawn(this, 0));

	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &AToonTowerPawn::CheckFireCondition, FireRate, true);
}


void AToonTowerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TankPlayerLocation = PlayerTank->GetActorLocation();
	DistanceToTank = FVector::Dist(GetActorLocation(), TankPlayerLocation);

	if (InFireRange())
	{
		RotateTurret(TankPlayerLocation);
	}
}

bool AToonTowerPawn::InFireRange()
{
	return DistanceToTank <= FireRange ? true : false;
}

void AToonTowerPawn::CheckFireCondition()
{
	if (PlayerTank)
	{
		if (InFireRange())
		{
			Fire();
		}
	}
}

