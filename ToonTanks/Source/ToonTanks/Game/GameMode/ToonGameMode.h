// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameOverDelegate, bool, bWonGame);

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonGameMode : public AGameModeBase
{
	GENERATED_BODY()
	

public:
	void ActorDied(AActor* DeadActor);

	UFUNCTION(BlueprintImplementableEvent)
	void BP_ActorDied(bool bIsPlayer);

	UFUNCTION(BlueprintImplementableEvent)
	void BP_GameStart();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void BP_GameOver(bool bWonGame);


	virtual void BeginPlay() override;
	virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnGameOverDelegate OnGameOver;

	UFUNCTION(BlueprintCallable)
	int32 GetEnemiesAliveCount() const;

private:
	// Player reference
	UPROPERTY(VisibleInstanceOnly, Category = "ToonGameMode", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class AToonPlayerPawn> PlayerPawn;

	UPROPERTY(VisibleInstanceOnly, Category = "ToonGameMode", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class AToonPlayerController> PlayerController;

	// Delay before game starts
	UPROPERTY(EditDefaultsOnly, Category = "ToonGameMode", meta = (InlineEditConditionToggle))
	bool bGameStartDelay = false;

	// Delay before game starts
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ToonGameMode", meta = (AllowPrivateAccess = "true", EditCondition = "bGameStartDelay"))
	float GameStartDelay = 3.f;

	// Number of turret towers in the level
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "ToonGameMode", meta = (AllowPrivateAccess = "true"))
	int32 EnemiesAliveCount = 0;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "ToonGameMode", meta = (AllowPrivateAccess = "true"))
	bool bGameWon = false;
};