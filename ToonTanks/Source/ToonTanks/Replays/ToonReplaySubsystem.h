// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ToonReplaySubsystem.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API UToonReplaySubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

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
	// TObjectPtr<UDemoNetDriver> DemoNetDriver;
};
