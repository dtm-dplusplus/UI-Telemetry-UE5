// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"

#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

ATower::ATower()
{
	FireRange = 500.f;
	FireRate = 3.f;
}


void ATower::BeginPlay()
{
	Super::BeginPlay();

	TankRef = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);

}

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TankRef)
	{
		if(InFireRange())
		{
			const FVector tankRefLocation = TankRef->GetActorLocation();
			RotateTurret(tankRefLocation);
		}
	}
}

bool ATower::InFireRange()
{
	const FVector tankRefLocation = TankRef->GetActorLocation();
	DistanceToTank = FVector::Dist(GetActorLocation(), tankRefLocation);

	if (DistanceToTank <= FireRange) return true;
	return false;
}

void ATower::CheckFireCondition()
{
	if(TankRef)
	{
		if (InFireRange())
		{
			Fire();
		}
	}
}
