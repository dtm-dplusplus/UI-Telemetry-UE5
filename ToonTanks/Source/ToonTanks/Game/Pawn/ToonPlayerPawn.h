// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ToonPawn.h"
#include "ToonPlayerPawn.generated.h"

class UInputAction;
struct FInputActionValue;
class UCameraShakeBase;

UCLASS()
class TOONTANKS_API AToonPlayerPawn : public AToonPawn
{
	GENERATED_BODY()

public:
	AToonPlayerPawn();

	virtual void Tick(float DeltaTime) override;


	/** Action */
	virtual void Fire() override;

	/**
	 * Additional destruction handling. Here we implement the camera shakes for player pawn camera
	 */
	virtual void OnDestroy() override;

private:
	///////////////////////////////////
	// Movement Properties
	///////////////////////////////////
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float MoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float TurnSpeed;

	/** Movement */
	/** Forwards & Backwards movement */
	void MoveForward(const FInputActionValue& Value);

	/**
	 * Left & Right Tank Base Rotaion
	 * The Camera is a child to the base mesh, so it will folllow this rotation
	 */
	void RotateBase(const FInputActionValue& Value);

	/** Rotates the turret based on the normal point of the mouse position on screen */
	void RotateTurretOnLook();

	///////////////////////////////////
	// Camera Properties
	///////////////////////////////////
	
	UPROPERTY(EditAnywhere, Category = "Camera")
	TObjectPtr<class UCameraComponent> Camera;

	UPROPERTY(EditAnywhere, Category = "Camera")
	TObjectPtr<class USpringArmComponent> SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera|Shake", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UCameraShakeBase> LaunchCameraShakeClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera|Shake", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UCameraShakeBase> DeathCameraShakeClass;
	
	///////////////////////////////////
	// Input
	///////////////////////////////////

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class AToonPlayerController> PlayerController;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	/** Mapping Context for input actions and controller */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputMappingContext> InputMapping;

	/** Input Actions */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> InputFire;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> InputMoveForward;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> InputRotateTurret;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> InputTurn;
};
