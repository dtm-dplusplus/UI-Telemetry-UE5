// Fill out your copyright notice in the Description page of Project Settings.


#include "ReplayGameInstance.h"

#include "Engine/DemoNetDriver.h"

UReplayGameInstance::UReplayGameInstance()
{
	RecordingName = "My Replay";
	UIRecordingName = "UI Replay";
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

void UReplayGameInstance::RestartReplay()
{
	if (const UWorld* world = GetWorld())
	{
		if (UDemoNetDriver* demoNetDriver = world->GetDemoNetDriver())
		{
			demoNetDriver->StopDemo();
			demoNetDriver->GotoTimeInSeconds(0);
		}
	}
}
