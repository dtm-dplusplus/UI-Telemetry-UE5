// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ToonProjectile.generated.h"

UCLASS()
class TOONTANKS_API AToonProjectile : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AToonProjectile();

	UFUNCTION()
	void SetDamageAmount(const float Amount) { DamageAmount = Amount; }

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);


private:
	// PROJECTILE PROPERTIES //
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> ProjectileMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UProjectileMovementComponent> ProjectileMovementComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projectile", meta = (AllowPrivateAccess = "true"))
	float DamageAmount = 40.f;

	// EFFECT | PARTICLES //
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "Effects", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UParticleSystemComponent> TrailParticleComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Effects", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UParticleSystem> HitParticles;

	// EFFECT | SOUND //
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Effects", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USoundBase> LaunchSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Effects", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USoundBase> HitSound;

	// EFFECT | CAMERA //
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Effects", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UCameraShakeBase> HitCameraShakeClass;
};
