// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonProjectile.h"

#include "Camera/CameraShakeBase.h"
#include "GameFramework/DamageType.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AToonProjectile::AToonProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set replication for replay functionality
	// Set replication for replay functionality
	bReplicates = true;
	AActor::SetReplicateMovement(true);

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	RootComponent = ProjectileMesh;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));

	ProjectileMovementComponent->InitialSpeed = 800.f;
	ProjectileMovementComponent->MaxSpeed = 950.f;

	ProjectileMesh->SetSimulatePhysics(true);

	TrailParticleComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Smoke Trail"));
	TrailParticleComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AToonProjectile::BeginPlay()
{
	Super::BeginPlay();

	ProjectileMesh->OnComponentHit.AddDynamic(this, &AToonProjectile::OnHit);

	// Play Launch sound
	if (LaunchSound)
	{
		UGameplayStatics::SpawnSoundAtLocation(this, LaunchSound, GetActorLocation());
	}
}

void AToonProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("Hit Object"))

	// Play Hit sound
	if (HitSound)
	{
		UGameplayStatics::SpawnSoundAtLocation(this, HitSound, GetActorLocation());
	}

	const auto myOwner = GetOwner();

	if (!myOwner)
	{
		Destroy();
		return;
	}

	const auto myOwnerInstigator = myOwner->GetInstigatorController();
	const auto damageTypeClass = UDamageType::StaticClass();

	if (OtherActor && OtherActor != this && OtherActor != myOwner)
	{
		
		if(float d = UGameplayStatics::ApplyDamage(OtherActor, DamageAmount, myOwnerInstigator, this, damageTypeClass))
			UE_LOG(LogTemp, Warning, TEXT("Applied %f damage to %s"), d, *OtherActor->GetName())
		if (HitParticles)
			UGameplayStatics::SpawnEmitterAtLocation(this, HitParticles, GetActorLocation(), GetActorRotation());

		if (HitCameraShakeClass)
			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShakeClass);
	}

	Destroy();
}

// Called every frame
void AToonProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

