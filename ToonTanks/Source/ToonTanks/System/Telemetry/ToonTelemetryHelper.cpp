// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTelemetryHelper.h"

DEFINE_LOG_CATEGORY(ToonTelemetry)

FString UToonTelemetryHelper::SessionDate{};

void UToonTelemetryHelper::InitializeTelemetryDirectory()
{
	SessionDate = GetDateTimeNowToString(true);
}
