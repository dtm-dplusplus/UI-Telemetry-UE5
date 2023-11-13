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

	void HandleGameStart();
	int32 GetTargetTowerCount() const;
protected:
	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bWonGame);
private:

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "GameMode", meta = (AllowPrivateAccess = "true"))
	class ATank* TankPlayer;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "GameMode", meta = (AllowPrivateAccess = "true"))
	class ATankPlayerController* TankPlayerController;

	

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GameMode", meta = (AllowPrivateAccess = "true"))
	float GameStartDelay = 3.f;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "GameMode", meta = (AllowPrivateAccess = "true"))
	int32 TargetTowers = 0;
};
