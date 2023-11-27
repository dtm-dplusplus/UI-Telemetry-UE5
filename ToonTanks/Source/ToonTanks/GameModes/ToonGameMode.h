// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	void ActorDied(AActor* DeadActor);
	void BeginPlay() override;
	void EndPlay(EEndPlayReason::Type EndPlayReason) override;

	

	int32 GetTargetTowerCount() const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UDataTable> ToonGameStatsTable;
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
	TObjectPtr<class AToonTankPawn> PlayerTank;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "TankGameMode", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class AToonPlayerController> TankPlayerController;

	// Delay before game starts
	UPROPERTY(EditAnywhere, Category = "TankGameMode", meta = (InlineEditConditionToggle))
	bool bGameStartDelay = false;

	// Delay before game starts
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "TankGameMode", meta = (AllowPrivateAccess = "true", EditCondition = "bGameStartDelay"))
	float GameStartDelay = 3.f;

	// Number of turret towers in the level
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "TankGameMode", meta = (AllowPrivateAccess = "true"))
	int32 EnemiesAliveCount = 0;
};
