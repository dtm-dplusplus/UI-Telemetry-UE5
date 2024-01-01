// Fill out your copyright notice in the Description page of Project Settings.

#include "ToonTelemetryInstance.h"
#include "ToonTelemetryHelper.h"

UToonTelemetryInstance::UToonTelemetryInstance()
{
	InstanceID = -1;
	FileDir = "";
	FilePath = "";
	FileName = "";
	FileColumns = {};
}

bool UToonTelemetryInstance::InitializeInstance(const int NewID, const FString& Name,
                                                const TArray<FString>& CustomColumns)
{
	// Set Instance Attributes
	InstanceID = NewID;

	FileDir = UToonTelemetryHelper::GetTelemetryDirectory();

	FileName = Name + " " + UToonTelemetryHelper::GetDateTimeNowToString(true);

	FilePath = FileDir + FileName + ".csv";

	FileColumns = CustomColumns;

	// Create CSV file with column names
	if (!UToonTelemetryHelper::WriteRowToFile(UToonTelemetryHelper::GetStringListToCSVString(FileColumns), FilePath))
	{
		UE_LOG(ToonTelemetry, Error, TEXT("Error - Create Telemetry Instance CSV File"));
		return false;
	}

	UE_LOG(ToonTelemetry, Display, TEXT("Success - Create Telemetry Instance CSV File"));

	return true;
}

void UToonTelemetryInstance::SaveEvent(const FString& EventName, const FString& EventCategory,
	const TArray<FString>& CustomColumnData) const
{
	// Save List to string - Default first, then additional columns
	TArray ColumnData = { UToonTelemetryHelper::GetDateTimeNowToString(), EventName, EventCategory };
	ColumnData.Append(CustomColumnData);

	// Write Row to file
	UToonTelemetryHelper::WriteRowToFile(UToonTelemetryHelper::GetStringListToCSVString(ColumnData), FilePath);
}