// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

struct FInputActionValue;
class UInputAction;

UCLASS()
class TOONTANKS_API ATank final : public ABasePawn
{
	GENERATED_BODY()

private:
	// INPUT MAPPINGS //
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tank|Enhanced Input", meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* InputMapping;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tank|Enhanced Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* InputMoveForward;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tank|Enhanced Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* InputBoost;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tank|Enhanced Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* InputTurn;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tank|Enhanced Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* InputRotateTurret;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tank|Enhanced Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* InputLook;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tank|Enhanced Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* InputFire;

	APlayerController* TankPlayerController;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
public:
	ATank();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void Move(const FInputActionValue& Value);
	void Turn(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	virtual void Fire() override;
	virtual void HandleDestruction() override;

	UFUNCTION(BlueprintCallable)
	APlayerController* GetTankController() const { return TankPlayerController; }

	UFUNCTION(BlueprintCallable)
	bool GetTankAlive() const { return bAlive; }
private:

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "Tank", meta = (AllowPrivateAccess = "true"))
	bool bAlive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tank|Movement", meta = (AllowPrivateAccess = "true"))
	float MovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tank|Movement", meta = (AllowPrivateAccess = "true"))
	float TurnSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tank|Movement", meta = (AllowPrivateAccess = "true"))
	float LookSpeed;

	UPROPERTY(EditAnywhere, Category = "Tank|Camera")
	class UCameraComponent* Camera;
							 
	UPROPERTY(EditAnywhere, Category = "Tank|Camera")
	class USpringArmComponent* SpringArm;

	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tank|Camera|Shake", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UCameraShakeBase> LaunchCameraShakeClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tank|Camera|Shake", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UCameraShakeBase> DeathCameraShakeClass;

};
