// Fill out your copyright notice in the Description page of Project Settings.


#include "toonpawn.h"

// Fill out your copyright notice in the Description page of Project Settings.
#include "ToonHealthComponent.h"
#include "Components/StaticMeshComponent.h"
#include "../Weapon/ToonProjectile.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AToonPawn::AToonPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set up components for blueprint
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	CapsuleComponent->SetSimulatePhysics(true);
	RootComponent = CapsuleComponent;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("Base Mesh");
	BaseMesh->SetupAttachment(RootComponent);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>("Turret Mesh");
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>("Spawn Point");
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);

	HealthComponent = CreateDefaultSubobject<UToonHealthComponent>("Health Component");

	// Set properties of  pawn
	TurretInterpRate = 10.f;
}

void AToonPawn::RotateTurret(const FVector& LookAtTarget) const
{
	const float DeltaT = UGameplayStatics::GetWorldDeltaSeconds(GetWorld());

	const FRotator TurretRotation = TurretMesh->GetComponentRotation();

	const FVector ToTarget = LookAtTarget - TurretMesh->GetComponentLocation();

	const FRotator LookAtRotation = { TurretRotation.Pitch, ToTarget.Rotation().Yaw,TurretRotation.Roll };

	TurretMesh->SetWorldRotation(
		FMath::RInterpTo(TurretRotation,LookAtRotation,DeltaT, TurretInterpRate));
}

void AToonPawn::Fire()
{
	const auto Projectile = GetWorld()->SpawnActor<AToonProjectile>(ProjectileClass, ProjectileSpawnPoint->GetComponentLocation(), ProjectileSpawnPoint->GetComponentRotation());
	Projectile->SetOwner(this);
	BP_Fire(Projectile);
}

void AToonPawn::OnDestroy()
{
	if (DeathParticles)
		UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticles, GetActorLocation(), GetActorRotation());

	if (DeathSound)
		UGameplayStatics::SpawnSoundAtLocation(this, DeathSound, GetActorLocation());

	Destroy();
}