// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ToonGameInstance.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(ToonGame, Log, All)

/**
 * 
 */




UCLASS()
class TOONTANKS_API UToonGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UToonGameInstance(const FObjectInitializer& ObjectInitializer);


};