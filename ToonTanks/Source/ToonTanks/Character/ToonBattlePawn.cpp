// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonBattlePawn.h"

// Fill out your copyright notice in the Description page of Project Settings.
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ToonHealthComponent.h"
#include "ToonTanks/Weapons/ToonProjectile.h"

// Sets default values
AToonBattlePawn::AToonBattlePawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set replication for replay functionality
	bReplicates = true;
	AActor::SetReplicateMovement(true);

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

	//HealthComponent = CreateDefaultSubobject<UToonHealthComponent>("Health Component");

	// Set properties of base pawn
	TurretInterpRate = 10.f;
	ProjectileDamageAmount = 10.f;
}

// Called when the game starts or when spawned
void AToonBattlePawn::BeginPlay()
{
	Super::BeginPlay();

	ProjetcilesFired = 0;
	EnemiesKilled = 0;
}

// Called every frame
void AToonBattlePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AToonBattlePawn::RotateTurret(const FVector& LookAtTarget)
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

void AToonBattlePawn::Fire()
{
	ProjetcilesFired++;

	// Spawn Projectile actor
	const auto projectile = GetWorld()->SpawnActor<AToonProjectile>(ProjectileClass, ProjectileSpawnPoint->GetComponentLocation(), ProjectileSpawnPoint->GetComponentRotation());
	
	// Set projectile properties
	projectile->SetDamageAmount(ProjectileDamageAmount);
	projectile->SetOwner(this);

	RecieveFire(projectile);
}

void AToonBattlePawn::OnDestroy()
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
