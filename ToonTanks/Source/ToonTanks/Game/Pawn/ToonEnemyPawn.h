// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ToonPawn.h"
#include "GameFramework/Pawn.h"
#include "ToonEnemyPawn.generated.h"

UCLASS()
class TOONTANKS_API AToonEnemyPawn : public AToonPawn
{
	GENERATED_BODY()

public:
	AToonEnemyPawn();
	void CheckFireCondition();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Tower", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<APawn> PlayerPawn;

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
