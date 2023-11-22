// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

class UCapsuleComponent;
class UHealthComponent;
UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	ABasePawn();

	virtual void HandleDestruction();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	// Actions //
	void RotateTurret(const FVector& LookAtTarget);

	virtual void Fire();

	// BASE COMPONENTS //
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BasePawn", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCapsuleComponent> CapsuleComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BasePawn", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> BaseMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BasePawn", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> TurretMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BasePawn", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> ProjectileSpawnPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BasePawn", meta = (AllowPrivateAccess = "true"))
	float TurretInterpRate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BasePawn", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UHealthComponent> HealthComponent;

	// EFFECT | PARTICLES //
	UPROPERTY(EditAnywhere, Category = "BasePawn|Projectile", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BasePawn|Projectile", meta = (AllowPrivateAccess = "true"))
	float ProjectileDamageAmount = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BasePawn|Effects", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UParticleSystem> DeathParticles;

	// EFFECT | SOUND //
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BasePawn|Effects", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USoundBase> DeathSound;

};
