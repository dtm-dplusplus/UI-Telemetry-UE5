// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"


UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projectile", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile", meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "Projectile", meta = (AllowPrivateAccess = "true"))
	UParticleSystemComponent* TrailParticleComponent;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile", meta = (AllowPrivateAccess = "true"))
	float Damgage = 40.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projectile", meta = (AllowPrivateAccess = "true"))
	UParticleSystem* HitParticles;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projectile", meta = (AllowPrivateAccess = "true"))
	UParticleSystem* TrailParticles;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projectile", meta = (AllowPrivateAccess = "true"))
	USoundBase* LaunchSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projectile", meta = (AllowPrivateAccess = "true"))
	USoundBase* HitSound;
};
