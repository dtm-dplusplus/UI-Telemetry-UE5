// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTelemetryInstance.h"

bool UToonTelemetryInstance::InitializeTelemetry(const int NewID, const FString& Name,
	const TArray<FString> CustomColumns)
{
	// Set InstanceID
	InstanceID = NewID;

	// Set File Directory
	FileDir = UToonTelemetryHelper::GetTelemetryDirectory();

	// Set File Name
	FileName = Name + " " + UToonTelemetryHelper::GetDateTimeNowToString(true);

	// Set File Path
	FilePath = FileDir + FileName + ".csv";

	// Add Colums to FileColumns
	FileColumns = CustomColumns;

	// Create CSV file with column names
	if (!WriteRowToFile(UToonTelemetryHelper::GetListToCSVString(CustomColumns)))
	{
		UE_LOG(ToonTelemetry, Error, TEXT("Error - Create Telemetry Instance CSV File"));
		return false;
	}

	UE_LOG(ToonTelemetry, Display, TEXT("Success - Create Telemetry Instance CSV File"));

	return true;
}



void UToonTelemetryInstance::SaveEvent(const FString& EventName, const FString& EventCategory,
	const TArray<FString>& CustomColumnValues)
{
	//// Save List to string - Default first, then additional columns
	TArray ColumnData = { UToonTelemetryHelper::GetDateTimeNowToString(), EventName, EventCategory };
	ColumnData.Append(CustomColumnValues);

	//// Write Row to file
	WriteRowToFile(UToonTelemetryHelper::GetListToCSVString(ColumnData));

}
