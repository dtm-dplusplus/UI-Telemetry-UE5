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


UCLASS()
class TOONTANKS_API UToonGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UToonGameInstance(const FObjectInitializer& ObjectInitializer);

private:

};