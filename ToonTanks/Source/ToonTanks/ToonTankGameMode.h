// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTankGameMode.generated.h"


UCLASS()
class TOONTANKS_API AToonTankGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	void ActorDied(AActor* DeadActor);
	virtual void BeginPlay() override;
	void EndPlay(EEndPlayReason::Type EndPlayReason);

	void HandleGameStart();
	int32 GetTargetTowerCount() const;

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bWonGame);

private:
	// Player reference
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "TankGameMode", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class ATank> TankPlayer;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "TankGameMode", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class ATankPlayerController> TankPlayerController;

	// Delay before game starts
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "TankGameMode", meta = (AllowPrivateAccess = "true"))
	float GameStartDelay = 3.f;

	// Number of turret towers in the level
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "TankGameMode", meta = (AllowPrivateAccess = "true"))
	int32 TargetTowers = 0;
};