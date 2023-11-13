// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

#include "Tower.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	RootComponent = ProjectileMesh;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));

	ProjectileMovementComponent->InitialSpeed = 50.f;
	ProjectileMovementComponent->MaxSpeed = 100.f;

	ProjectileMesh->SetSimulatePhysics(true);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	const auto myOwner = GetOwner();

	if (!myOwner)
	{
		Destroy();
		return;
	}

	const auto myOwnerInstigator = myOwner->GetInstigatorController();
	const auto damageTypeClass = UDamageType::StaticClass();

	if(OtherActor && OtherActor != this && OtherActor != myOwner)
	{
		UGameplayStatics::ApplyDamage(OtherActor, Damgage, myOwnerInstigator, this, damageTypeClass);
		if(HitParticles)
			UGameplayStatics::SpawnEmitterAtLocation(this, HitParticles, GetActorLocation(), GetActorRotation());
	}
	Destroy();

}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

