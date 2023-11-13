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
private:

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "Tank", meta = (AllowPrivateAccess = "true"))
	class ATank* TankPlayer;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "Tank", meta = (AllowPrivateAccess = "true"))
	APlayerController* TankController;
};
