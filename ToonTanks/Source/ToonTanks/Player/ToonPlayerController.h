// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ToonPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AToonPlayerController(const FObjectInitializer& ObjectInitializer);
	void SetPlayerEnbaledState(bool bPlayerEnabled);
};


// A player controller used for replay capture and playback
UCLASS()
class AToonReplayPlayerController : public AToonPlayerController
{
	GENERATED_BODY()

	virtual void SetPlayer(UPlayer* InPlayer) override;
};
