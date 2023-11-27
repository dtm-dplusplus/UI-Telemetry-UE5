// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Engine/GameInstance.h"
#include "ToonTanks/Player/ToonPlayerController.h"
#include "ToonGameInstance.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FToonGameStats: public FTableRowBase {
	GENERATED_BODY()

public:
	FToonGameStats() : ProjectilesFired(0), ProjectilesHit(0), EnemiesKilled(0) {}


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameStats")
	FString RowName;

	FTimespan TimeStamp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameStats")
	FString PlayerName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameStats")
	int32 ProjectilesFired;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameStats")
	int32 ProjectilesHit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameStats")
	int32 EnemiesKilled;
};

UCLASS()
class TOONTANKS_API UToonGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UToonGameInstance(const FObjectInitializer& ObjectInitializer);

private:

};