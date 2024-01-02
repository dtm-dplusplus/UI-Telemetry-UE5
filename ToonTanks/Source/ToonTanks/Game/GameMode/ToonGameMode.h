// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameFramework/GameModeBase.h"
#include "ToonGameMode.generated.h"

USTRUCT(BlueprintType)
struct FToonGameStats : public FTableRowBase {
	GENERATED_BODY()

public:
	FToonGameStats() : ProjectilesFired(0), ProjectilesHit(0), EnemiesKilled(0) {}


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Telementary|Pawn")
	FString RowName;

	FTimespan TimeStamp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Telementary|Pawn")
	FString PlayerName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Telementary|Pawn")
	int32 ProjectilesFired;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Telementary|Pawn")
	int32 ProjectilesHit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Telementary|Pawn")
	int32 EnemiesKilled;
};

USTRUCT(BlueprintType)
struct FToonProjectileData : public FTableRowBase {
	GENERATED_BODY()

public:
	FToonProjectileData() : GameSessionTimeStamp(FDateTime::Now()), ProjetcileOwner("Owner"), ProjectileType("") {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Telementary|Projectile")
	FDateTime WorldTimeStamp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Telementary|Projectile")
	FDateTime GameSessionTimeStamp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Telementary|Projectile")
	FString ProjetcileOwner;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Telementary|Projectile")
	FString ProjectileType;
};

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
	void RecieveActorDied(bool bIsPlayer);

	void BeginPlay() override;
	void EndPlay(EEndPlayReason::Type EndPlayReason) override;



	int32 GetEnemiesAliveCount() const;

	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveStartGame();

	void GameOver(bool bWonGame);

	UFUNCTION(BlueprintImplementableEvent)
	void RecieveGameOver(bool bWonGame);



private:
	// Player reference
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "TankGameMode", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class AToonPlayerPawn> PlayerTank;

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
