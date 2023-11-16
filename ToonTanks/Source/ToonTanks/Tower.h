// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"


UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()

public:
	ATower();

	void CheckFireCondition();
	virtual void HandleDestruction() override;
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Tower", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class ATank> PlayerTank;

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
