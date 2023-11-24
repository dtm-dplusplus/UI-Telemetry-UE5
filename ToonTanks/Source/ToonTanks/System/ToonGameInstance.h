// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

	UFUNCTION(BlueprintCallable, Category = "Replay")
	void SetRecordGameplay(bool bRecord);

	UFUNCTION(BlueprintCallable, Category = "Replay")
	bool GetRecordGameplay() const;

	AToonPlayerController* GetPrimaryPlayerController() const;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Replay", meta = (AllowPrivateAccess = "true"))
	bool bRecordGameplay = true;
};
