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
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	RootComponent = ProjectileMesh;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));

	ProjectileMovementComponent->InitialSpeed = 400.f;
	ProjectileMovementComponent->MaxSpeed = 400.f;


	TrailParticleComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Smoke Trail"));
	TrailParticleComponent->SetupAttachment(RootComponent);

	ProjectileMesh->SetSimulatePhysics(true);
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
	// Play Hit sound
	if (HitSound) UGameplayStatics::SpawnSoundAtLocation(this, HitSound, GetActorLocation());

	const auto MyOwner = GetOwner();

	if (!MyOwner)
	{
		Destroy();
		return;
	}

	

	// Here we apply damage if the actor is a pawn
	if (OtherActor && OtherActor != this && OtherActor != MyOwner)
	{
		if (HitParticles)
			UGameplayStatics::SpawnEmitterAtLocation(this, HitParticles, GetActorLocation(), GetActorRotation());

		const TObjectPtr<AController> MyOwnerInstigator = MyOwner->GetInstigatorController();
		const TObjectPtr<UClass> DamageTypeClass = UDamageType::StaticClass();

		if(Cast<APawn>(OtherActor))
			UGameplayStatics::ApplyDamage(OtherActor, DamageAmount, MyOwnerInstigator, this, DamageTypeClass);

		// If player collision, shake the pawn camera
		if (HitCameraShakeClass && UGameplayStatics::GetPlayerPawn(this, 0) == Cast<APawn>(OtherActor))
			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShakeClass);
	}

	Destroy();
}