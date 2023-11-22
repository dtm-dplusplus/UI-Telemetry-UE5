// Fill out your copyright notice in the Description page of Project Settings.


#include "ReplayPlayerController.h"

#include "Engine/DemoNetDriver.h"
#include "Engine/World.h"

// void AReplayPlayerController::OnPauseReplay()
// {
// }
// 
// void AReplayPlayerController::OnRestartRecording()
// {
// }
AReplayPlayerController::AReplayPlayerController()
{
	bShowMouseCursor = false;
	DefaultMouseCursor = EMouseCursor::None;
}
