// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"

ATower::ATower()
{
}

void ATower::BeginPlay()
{
	Super::BeginPlay();


	TankRef = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TankRef)
	{
		const FVector tankRefLocation = TankRef->GetActorLocation();
		const float distance = FVector::Dist(GetActorLocation(), tankRefLocation);
		if(distance <= FireRange)
		{
			RotateTurret(tankRefLocation);
		}
	}
}
