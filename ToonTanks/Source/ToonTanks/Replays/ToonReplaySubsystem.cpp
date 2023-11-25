//// Fill out your copyright notice in the Description page of Project Settings.
//
//
#include "ToonReplaySubsystem.h"

#include "Engine/DemoNetDriver.h"

void UToonReplaySubsystem::PlayReplay(UToonReplayEntry* Replay)
{
	if (Replay)
	{
		GetGameInstance()->PlayReplay(Replay->StreamInfo.Name);
	}
}

// void ULyraReplaySubsystem::DeleteReplay()
// {
//	ReplayStreamer->DeleteFinishedStream(SelectedItem->StreamInfo.Name, FDeleteFinishedStreamCallback::CreateSP(this, &SShooterDemoList::OnDeleteFinishedStreamComplete));
// }

void UToonReplaySubsystem::SeekInActiveReplay(float TimeInSeconds)
{
	if (UDemoNetDriver* DemoDriver = GetDemoDriver())
	{
		DemoDriver->GotoTimeInSeconds(TimeInSeconds);
	}
}

float UToonReplaySubsystem::GetReplayLengthInSeconds() const
{
	if (UDemoNetDriver* DemoDriver = GetDemoDriver())
	{
		return DemoDriver->GetDemoTotalTime();
	}
	return 0.0f;
}

float UToonReplaySubsystem::GetReplayCurrentTime() const
{
	if (UDemoNetDriver* demoDriver = GetDemoDriver())
	{
		return demoDriver->GetDemoCurrentTime();
	}
	return 0.0f;
}

UDemoNetDriver* UToonReplaySubsystem::GetDemoDriver() const
{
	if (UWorld* World = GetGameInstance()->GetWorld())
	{
		return World->GetDemoNetDriver();
	}
	return nullptr;
}

