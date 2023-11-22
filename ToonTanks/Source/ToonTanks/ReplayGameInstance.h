// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ReplayGameInstance.generated.h"

UCLASS()
class TOONTANKS_API UReplayGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UReplayGameInstance();

	UFUNCTION(BlueprintCallable, Category = "Replay")
	void StartRecording();

	UFUNCTION(BlueprintCallable, Category = "Replay")
	void StopRecording();

	UFUNCTION(BlueprintCallable, Category = "Replay")
	void StartReplay();

	UFUNCTION(BlueprintCallable, Category = "Replay")
	void StopReplay();

private:
	UPROPERTY(EditDefaultsOnly, Category = "Replay", meta = (AllowPrivateAccess = "true"))
	FString RecordingName;

	UPROPERTY(EditDefaultsOnly, Category = "Replay", meta = (AllowPrivateAccess = "true"))
	FString UIRecordingName;
};
