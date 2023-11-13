// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

struct FInputActionValue;

UCLASS()
class TOONTANKS_API ATank final : public ABasePawn
{
	GENERATED_BODY()

public:
	ATank();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void Move(const FInputActionValue& Value);
	// void Boost(const FInputActionValue& Value);
	void Turn(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);


private:
	

	// UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	// float BoostSpeed;
	// 
	// UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	// float BoostTime;
	// 
	// UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	// float BoostCoolDownTime;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Tank|Movement", meta = (AllowPrivateAccess = "true"))
	float MovementSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Tank|Movement", meta = (AllowPrivateAccess = "true"))
	float TurnSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Tank", meta = (AllowPrivateAccess = "true"))
	float LookSpeed;

	UPROPERTY(EditDefaultsOnly, Category = "Tank|Components")
	class UCameraComponent* Camera;
							 
	UPROPERTY(EditDefaultsOnly, Category = "Tank|Components")
	class USpringArmComponent* SpringArm;

	//Setting up inputs. Mapping context and Input Action variables, to be set in Blueprint
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tank|Enhanced Input", meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* InputMapping;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tank|Enhanced Input", meta = (AllowPrivateAccess = "true"))
	class UInputAction* InputMoveForward;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tank|Enhanced Input", meta = (AllowPrivateAccess = "true"))
	class UInputAction* InputBoost;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tank|Enhanced Input", meta = (AllowPrivateAccess = "true"))
	class UInputAction* InputTurn;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tank|Enhanced Input", meta = (AllowPrivateAccess = "true"))
	class UInputAction* InputRotateTurret;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tank|Enhanced Input", meta = (AllowPrivateAccess = "true"))
	class UInputAction* InputLook;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tank|Enhanced Input", meta = (AllowPrivateAccess = "true"))
	class UInputAction* InputFire;

	APlayerController* PlayerControllerRef;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
};
