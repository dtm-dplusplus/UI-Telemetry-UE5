// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ToonBattlePawn.h"
#include "ToonTowerPawn.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTowerPawn : public AToonBattlePawn
{
	GENERATED_BODY()

public:
	AToonTowerPawn();

	void CheckFireCondition();
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Tower", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class AToonTankPawn> PlayerTank;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Tower", meta = (AllowPrivateAccess = "true"))
	FVector TankPlayerLocation;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Tower", meta = (AllowPrivateAccess = "true"))
	float DistanceToTank;

	UFUNCTION(BlueprintCallable)
	bool InFireRange();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tower", meta = (AllowPrivateAccess = "true"))
	float FireRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tower", meta = (AllowPrivateAccess = "true"))
	float FireRate;

	FTimerHandle FireRateTimerHandle;
};
