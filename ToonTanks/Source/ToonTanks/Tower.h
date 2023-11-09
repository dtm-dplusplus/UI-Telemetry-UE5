// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()

public:
	ATower();
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float FireRange;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	class ATank* TankRef;
};
