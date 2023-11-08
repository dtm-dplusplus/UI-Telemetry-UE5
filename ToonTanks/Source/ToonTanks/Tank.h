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

	void BeginPlay() override;
	void Move(const FInputActionValue& Value);
private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UCameraComponent* Camera;
							 
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USpringArmComponent* SpringArm;

	//Setting up inputs. Mapping context and Input Action variables, to be set in Blueprint
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input", meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* InputMapping;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input", meta = (AllowPrivateAccess = "true"))
	class UInputAction* InputMoveForward;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input", meta = (AllowPrivateAccess = "true"))
	class UInputAction* InputTurn;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input", meta = (AllowPrivateAccess = "true"))
	class UInputAction* InputRotateTurret;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input", meta = (AllowPrivateAccess = "true"))
	class UInputAction* InputFire;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
};
