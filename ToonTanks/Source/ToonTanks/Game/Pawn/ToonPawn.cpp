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
	ProjectileDamage = 50.f;
	ProjectileSpeed = 100.f;
}

void AToonPawn::RotateTurret(const FVector& LookAtTarget)
{
	const float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(GetWorld());

	const FVector ToTarget = LookAtTarget - TurretMesh->GetComponentLocation();
	FRotator LookAtRotation = ToTarget.Rotation();
	LookAtRotation.Pitch = 0.0f;
	LookAtRotation.Roll = 0.0f;

	TurretMesh->SetWorldRotation(
		FMath::RInterpTo(
			TurretMesh->GetComponentRotation(),
			LookAtRotation,
			DeltaTime,
			TurretInterpRate));
}

void AToonPawn::Fire()
{
	// Spawn Projectile actor
	const auto Projectile = GetWorld()->SpawnActor<AToonProjectile>(ProjectileClass, ProjectileSpawnPoint->GetComponentLocation(), ProjectileSpawnPoint->GetComponentRotation());

	// Set projectile properties
	Projectile->InitializeProjectile(ProjectileDamage, 1000);
	Projectile->SetOwner(this);

	RecieveFire(Projectile);
}

void AToonPawn::OnDestroy()
{
	// Spawn death particls
	if (DeathParticles)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticles, GetActorLocation(), GetActorRotation());
	}

	// Play death sound
	if (DeathSound)
	{
		UGameplayStatics::SpawnSoundAtLocation(this, DeathSound, GetActorLocation());
	}

	Destroy();
}
