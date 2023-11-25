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

	AToonGameMode();
	void ActorDied(AActor* DeadActor);
	virtual void BeginPlay() override;
	virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;

	int32 GetTargetTowerCount() const;

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

	// Delay before game starts
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "TankGameMode", meta = (AllowPrivateAccess = "true"))
	bool bGameStartDelay = false;

	// Delay before game starts
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "TankGameMode", meta = (AllowPrivateAccess = "true"))
	float GameStartDelay = 3.f;

	// Number of turret towers in the level
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "TankGameMode", meta = (AllowPrivateAccess = "true"))
	int32 TargetTowers = 0;
};
