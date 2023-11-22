// Fill out your copyright notice in the Description page of Project Settings.


#include "ReplayGameInstance.h"

UReplayGameInstance::UReplayGameInstance()
{
	int randomNumber = FMath::RandRange(0, 100);
	RecordingName = "My Replay" + randomNumber;
	UIRecordingName = "UI Replay" + randomNumber;
}

void UReplayGameInstance::StartRecording()
{
	TArray<FString> urlOptions;
	urlOptions.Add("ReplayStreamerOverride=InMemoryReplayStreaming");
	StartRecordingReplay(RecordingName, UIRecordingName, urlOptions);
}

void UReplayGameInstance::StopRecording()
{
	StopRecordingReplay();
}

void UReplayGameInstance::StartReplay()
{
	PlayReplay(RecordingName, nullptr);
}

void UReplayGameInstance::StopReplay()
{
}
