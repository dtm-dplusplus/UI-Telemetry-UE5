// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"

#include "Projectile.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "HealthComponent.h"


// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set replication for replay functionality
    SetReplicates(true);
    AActor::SetReplicateMovement(true);

	// Set up components for blueprint
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	CapsuleComponent->SetSimulatePhysics(true);
	RootComponent= CapsuleComponent;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("Base Mesh");
	BaseMesh->SetupAttachment(RootComponent);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>("Turret Mesh");
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>("Spawn Point");
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>("Health Component");

	// Set properties of base pawn
	TurretInterpRate = 10.f;

}

// Called when the game starts or when spawned
void ABasePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABasePawn::RotateTurret(const FVector& LookAtTarget)
{
	const float deltaTime = UGameplayStatics::GetWorldDeltaSeconds(GetWorld());

	const FVector toTarget = LookAtTarget - TurretMesh->GetComponentLocation();
	FRotator lookAtRotation = toTarget.Rotation();
	lookAtRotation.Pitch = 0.0f;
	lookAtRotation.Roll = 0.0f;

	TurretMesh->SetWorldRotation(
		FMath::RInterpTo(
			TurretMesh->GetComponentRotation(),
			lookAtRotation,
			deltaTime,
			TurretInterpRate));
}

void ABasePawn::Fire()
{
	const auto projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectileSpawnPoint->GetComponentLocation(), ProjectileSpawnPoint->GetComponentRotation());
	projectile->SetDamageAmount(ProjectileDamageAmount);
	projectile->SetOwner(this);
}

void ABasePawn::HandleDestruction()
{
	// Spawn death particls
	if (DeathParticles)
		UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticles, GetActorLocation(), GetActorRotation());

	// Play death sound
	if (DeathSound)
		UGameplayStatics::SpawnSoundAtLocation(this, DeathSound, GetActorLocation());
}
