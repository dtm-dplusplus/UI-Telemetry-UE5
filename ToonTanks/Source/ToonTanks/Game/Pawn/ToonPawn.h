// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ToonPawn.generated.h"

class UToonHealthComponent;
class AToonProjectile;

/**
 * Base class which provides the majority of functionality to enemy and player pawns
 */
UCLASS()
class TOONTANKS_API AToonPawn : public APawn
{
	GENERATED_BODY()

public:
	AToonPawn();

	/** Spawns and fires a ToonProjectile */
	virtual void Fire();

	/** Notifies Blueprint on Fire() */
	UFUNCTION(BlueprintImplementableEvent)
	void BP_Fire(AToonProjectile* ProjectileFired);

	/** Called On Destruct */
	virtual void OnDestroy();

	/** Notifies Blueprint on Destruct() */
	UFUNCTION(BlueprintImplementableEvent)
	void BP_Destroy();

protected:

	// Actions //
	void RotateTurret(const FVector& LookAtTarget) const;

	/////////////////////////////////////////////
	// Actor Scene Components
	/////////////////////////////////////////////

	/** Collision capsule used for collision events on pawn */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ToonPawn", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCapsuleComponent> CapsuleComponent;

	/** The base mesh of the pawn */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ToonPawn", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> BaseMesh;

	/** The Turret mesh. Projectiles are fired through this */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ToonPawn", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> TurretMesh;

	/** Projectile fire point. Use the Scene component to set this relative to the pawn mesh */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ToonPawn", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> ProjectileSpawnPoint;

	/** The inrerp rate for turret rotation. Higher values will make pawn respond faster to rotation input */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ToonPawn", meta = (AllowPrivateAccess = "true"))
	float TurretInterpRate;


	/////////////////////////////////////////////
	// Weapons + Health
	/////////////////////////////////////////////
	
	/** Actor Component used to store information related to health */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ToonPawn", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UToonHealthComponent> HealthComponent;
	
	/** The type of projectile to be spawned. Currently only one type of class */
	UPROPERTY(EditAnywhere, Category = "ToonPawn", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AToonProjectile> ProjectileClass;

	/////////////////////////////////////////////
	// Effects
	/////////////////////////////////////////////

	/** The particles spawned when this pawn destructs */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ToonPawn|Effects", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UParticleSystem> DeathParticles;

	/** The sound played when this pawn destructs */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ToonPawn|Effects", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USoundBase> DeathSound;
};
