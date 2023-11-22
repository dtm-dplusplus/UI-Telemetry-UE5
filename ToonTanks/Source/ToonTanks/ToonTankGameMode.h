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
	void BeginPlay() override;
	void EndPlay(EEndPlayReason::Type EndPlayReason) override;

	int32 GetTargetTowerCount() const;

protected:
	void StartGame();

	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveStartGame();

	void GameOver(bool bWonGame);

	UFUNCTION(BlueprintImplementableEvent)
	void RecieveGameOver(bool bWonGame);

private:
	// Player reference
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "TankGameMode", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class ATank> TankPlayer;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "TankGameMode", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class ATankPlayerController> TankPlayerController;

	// Delay before game starts
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "TankGameMode", meta = (AllowPrivateAccess = "true"))
	bool bGameStartDelay = false;

	// Delay before game starts
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "TankGameMode", meta = (AllowPrivateAccess = "true"))
	float GameStartDelay = 3.f;

	// Number of turret towers in the level
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "TankGameMode", meta = (AllowPrivateAccess = "true"))
	int32 TargetTowers = 0;

	// REPLAY //
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "TankGameMode|Replay", meta = (AllowPrivateAccess = "true"))
	bool bRecordGameplay = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TankGameMode|Replay", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UReplayGameInstance> ReplayGameInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TankGameMode|Replay", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class AReplayPlayerController> ReplayPlayerController;
};