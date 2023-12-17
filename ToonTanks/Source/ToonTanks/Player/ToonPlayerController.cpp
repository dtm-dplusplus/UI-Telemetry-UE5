// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonPlayerController.h"
#include "GameFramework/Pawn.h"

AToonPlayerController::AToonPlayerController()
{
	bShowMouseCursor = true;
	// DefaultMouseCursor = EMouseCursor::Crosshairs;

}

void AToonPlayerController::SetPlayerEnbaledState(const bool bPlayerEnabled)
{
	if (bPlayerEnabled)
	{
		GetPawn()->EnableInput(this);
	}
	else
	{
		GetPawn()->DisableInput(this);
	}

	bShowMouseCursor = bPlayerEnabled;
}
