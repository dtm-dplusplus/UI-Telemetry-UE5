// Fill out your copyright notice in the Description page of Project Settings.


#include "ReplayPlayerController.h"

#include "Engine/DemoNetDriver.h"
#include "Engine/World.h"

void AReplayPlayerController::RestartRecording()
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
