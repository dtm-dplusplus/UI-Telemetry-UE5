// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonGameInstance.h"

#include "ToonTanks/Player/ToonPlayerController.h"

UToonGameInstance::UToonGameInstance(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UToonGameInstance::SetRecordGameplay(const bool bRecord)
{
	bRecordGameplay = bRecord;
}

bool UToonGameInstance::GetRecordGameplay() const
{
	return bRecordGameplay;
}

AToonPlayerController* UToonGameInstance::GetPrimaryPlayerController() const
{
	return Cast<AToonPlayerController>(Super::GetPrimaryPlayerController(false));
}
