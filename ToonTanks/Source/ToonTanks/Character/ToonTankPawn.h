// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ToonBattlePawn.h"
#include "ToonTankPawn.generated.h"

class UInputAction;
struct FInputActionValue;
class UCameraShakeBase;
/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTankPawn : public AToonBattlePawn
{
	GENERATED_BODY()

public:
	AToonTankPawn();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void Move(const FInputActionValue& Value);
	void Turn(const FInputActionValue& Value);
	void Look();
	virtual void Fire() override;
	virtual void OnDestroy() override;


private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float MovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float TurnSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float LookSpeed;

	// Camera Properties //
	UPROPERTY(EditAnywhere, Category = "Camera")
	TObjectPtr<class UCameraComponent> Camera;

	UPROPERTY(EditAnywhere, Category = "Camera")
	TObjectPtr<class USpringArmComponent> SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera|Shake", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UCameraShakeBase> LaunchCameraShakeClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera|Shake", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UCameraShakeBase> DeathCameraShakeClass;

	// Input Properties //
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputMappingContext> InputMapping;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> InputMoveForward;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> InputBoost;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> InputTurn;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> InputRotateTurret;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> InputLook;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> InputFire;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<APlayerController> TankPlayerController;

	// Called to bind functionality to input
	void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
};
