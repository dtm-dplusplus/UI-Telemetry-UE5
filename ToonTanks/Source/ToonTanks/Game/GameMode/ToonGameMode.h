// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameOverDelegate, bool, bWonGame);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameStartDelegate);


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

	/** Game Start */ 
	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnGameStartDelegate OnGameStartDelegate;

	/** Game Over */
	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnGameOverDelegate OnGameOverDelegate;

	UFUNCTION(BlueprintCallable)
	int32 GetEnemiesAliveCount() const;

protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;
private:
	// Player reference
	UPROPERTY(VisibleInstanceOnly, Category = "ToonGameMode", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class AToonPlayerPawn> PlayerPawn;

	UPROPERTY(VisibleInstanceOnly, Category = "ToonGameMode", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class AToonPlayerController> PlayerController;

	// Number of turret towers in the level
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "ToonGameMode", meta = (AllowPrivateAccess = "true"))
	int32 EnemiesAliveCount = 0;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "ToonGameMode", meta = (AllowPrivateAccess = "true"))
	bool bGameWon = false;
};