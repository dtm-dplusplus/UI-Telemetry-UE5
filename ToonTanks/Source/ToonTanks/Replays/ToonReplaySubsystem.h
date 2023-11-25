// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NetworkReplayStreaming.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ToonReplaySubsystem.generated.h"

/**
 * 
 */
 // An available replay
UCLASS(BlueprintType)
class UToonReplayEntry : public UObject
{
	GENERATED_BODY()

public:
	FNetworkReplayStreamInfo StreamInfo;

	/** The UI friendly name of the stream */
	UFUNCTION(BlueprintPure, Category = Replays)
	FString GetFriendlyName() const { return StreamInfo.FriendlyName; }

	/** The date and time the stream was recorded */
	UFUNCTION(BlueprintPure, Category = Replays)
	FDateTime GetTimestamp() const { return StreamInfo.Timestamp; }

	/** The duration of the stream in MS */
	UFUNCTION(BlueprintPure, Category = Replays)
	FTimespan GetDuration() const { return FTimespan::FromMilliseconds(StreamInfo.LengthInMS); }

	/** True if the stream is live and the game hasn't completed yet */
	UFUNCTION(BlueprintPure, Category = Replays)
	bool GetIsLive() const { return StreamInfo.bIsLive; }
};

UCLASS()
class TOONTANKS_API UToonReplaySubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = Replays)
	void PlayReplay(UToonReplayEntry* Replay);

	//void DeleteReplay();

	UFUNCTION(BlueprintCallable, Category = Replays)
	void SeekInActiveReplay(float TimeInSeconds);

	UFUNCTION(BlueprintCallable, Category = Replays, BlueprintPure = false)
	float GetReplayLengthInSeconds() const;

	UFUNCTION(BlueprintCallable, Category = Replays, BlueprintPure = false)
	float GetReplayCurrentTime() const;

private:
	UDemoNetDriver* GetDemoDriver() const;

	TObjectPtr<UDemoNetDriver> DemoNetDriver;

	// Recording //
	// UFUNCTION(BlueprintCallable, Category = "Replay|Recording")
	// void StartRecording();
	// 
	// UFUNCTION(BlueprintCallable, Category = "Replay|Recording")
	// void StopRecording();
	// 
	// bool GetStopRecordingDelay() const { return bStopRecordingDelay; }
	// 
	// float GetStopRecordingDelayTime() const { return StopRecordingDelay; }
	// 
	// // Replay //
	// UFUNCTION(BlueprintCallable, Category = "Replay|Playback")
	// void StartReplay();
	// 
	// UFUNCTION(BlueprintCallable, Category = "Replay|Playback")
	// void StopReplay();
	// 
	// UFUNCTION(BlueprintCallable, Category = "Replay|Playback")
	// void RestartReplay();



private:
	// Recording //
	// UPROPERTY(EditDefaultsOnly, Category = "Replay|Recording", meta = (AllowPrivateAccess = "true"))
	// FString RecordingName;
	// 
	// UPROPERTY(EditDefaultsOnly, Category = "Replay|Recording", meta = (AllowPrivateAccess = "true"))
	// FString UIRecordingName;
	// 
	// // Delay before game starts
	// UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Replay|Recording", meta = (AllowPrivateAccess = "true"))
	// bool bStopRecordingDelay = true;
	// 
	// // Delay before game starts
	// UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Replay|Recording", meta = (AllowPrivateAccess = "true"))
	// float StopRecordingDelay = 1.5f;
	// 
	// UPROPERTY(VisibleInstanceOnly, Category = "Replay")
	// TObjectPtr<UGameInstance> ToonGameInstance;
	// 
	// UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "Replay", meta = (AllowPrivateAccess = "true"))
	// 
};
