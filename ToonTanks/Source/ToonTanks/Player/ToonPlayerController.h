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
	AToonPlayerController();

	/**
	 * Toggle for player input. If false, input is disabled
	 * @param bPlayerEnabled - Enable or disable input
	 */
	UFUNCTION(BlueprintCallable)
	void SetPlayerInputState(bool bPlayerEnabled);

};
