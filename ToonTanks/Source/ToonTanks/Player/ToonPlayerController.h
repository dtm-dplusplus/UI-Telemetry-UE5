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
	void SetPlayerEnbaledState(bool bPlayerEnabled);

};
