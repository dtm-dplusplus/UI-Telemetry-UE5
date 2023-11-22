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

	// Recording //
	UFUNCTION(BlueprintCallable, Category = "Replay|Recording")
	void StartRecording();

	UFUNCTION(BlueprintCallable, Category = "Replay|Recording")
	void StopRecording();

	bool GetStopRecordingDelay() const { return bStopRecordingDelay; }

	float GetStopRecordingDelayTime() const { return StopRecordingDelay; }

	// Replay //
	UFUNCTION(BlueprintCallable, Category = "Replay|Playback")
	void StartReplay();

	UFUNCTION(BlueprintCallable, Category = "Replay|Playback")
	void StopReplay();

	UFUNCTION(BlueprintCallable, Category = "Replay|Playback")
	void RestartReplay();

	

private:
	// Recording //
	UPROPERTY(EditDefaultsOnly, Category = "Replay|Recording", meta = (AllowPrivateAccess = "true"))
	FString RecordingName;

	UPROPERTY(EditDefaultsOnly, Category = "Replay|Recording", meta = (AllowPrivateAccess = "true"))
	FString UIRecordingName;

	// Delay before game starts
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Replay|Recording", meta = (AllowPrivateAccess = "true"))
	bool bStopRecordingDelay = true;

	// Delay before game starts
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Replay|Recording", meta = (AllowPrivateAccess = "true"))
	float StopRecordingDelay = 1.5f;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "Replay", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UDemoNetDriver> DemoNetDriver;
};
