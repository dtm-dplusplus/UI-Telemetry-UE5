// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ToonPawn.h"
#include "ToonBattlePawn.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonBattlePawn : public AToonPawn
{
	GENERATED_BODY()

public:
	virtual void OnDestroy();
	virtual void Fire();

	virtual void Tick(float DeltaTime) override;

protected:
	AToonBattlePawn();
	virtual void BeginPlay() override;

	// Actions //
	void RotateTurret(const FVector& LookAtTarget);

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "Tank", meta = (AllowPrivateAccess = "true"))
	bool bAlive;

	// Mesh Components //
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BasePawn", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCapsuleComponent> CapsuleComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BasePawn", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> BaseMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BasePawn", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> TurretMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BasePawn", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> ProjectileSpawnPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BasePawn", meta = (AllowPrivateAccess = "true"))
	float TurretInterpRate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BasePawn", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UToonHealthComponent> HealthComponent;

	// EFFECT | PARTICLES //
	UPROPERTY(EditAnywhere, Category = "BasePawn|Projectile", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AToonProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BasePawn|Projectile", meta = (AllowPrivateAccess = "true"))
	float ProjectileDamageAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BasePawn|Effects", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UParticleSystem> DeathParticles;

	// EFFECT | SOUND //
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BasePawn|Effects", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USoundBase> DeathSound;
};
