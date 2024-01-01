// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTelemetrySubsystem.h"
#include "Telemetry/ToonTelemetryInstance.h"
#include "Telemetry/ToonTelemetryHelper.h"


void UToonTelemetrySubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	// Init telemetry attributes
	TelemetryIDCount = 0;

	// Check Telemetry Directory Exists. If not, create it.
	if (IPlatformFile& FM = FPlatformFileManager::Get().GetPlatformFile(); !FM.DirectoryExists(*UToonTelemetryHelper::GetTelemetryDirectory()))
	{
		UE_LOG(ToonTelemetry, Warning, TEXT("Telemetry Directory Does not exist"));

		if (FM.CreateDirectory(*UToonTelemetryHelper::GetTelemetryDirectory()))
		{
			UE_LOG(ToonTelemetry, Display, TEXT("Success - Create Telemetry Directory"));
		}
		else
		{
			UE_LOG(ToonTelemetry, Error, TEXT("Error - Create Telemetry Directory "));
		}
	}

	UE_LOG(ToonTelemetry, Display, TEXT("Toon Telemetry Subsystem Initialised"))
}

void UToonTelemetrySubsystem::Deinitialize()
{
	Super::Deinitialize();

	UE_LOG(ToonTelemetry, Display, TEXT("UToonTelemetrySubsystem Deinitialised"))
}

UToonTelemetryInstance* UToonTelemetrySubsystem::CreateTelemetryInstance(const FString& Name, TArray<FString> ExtraColumns)
{
	UE_LOG(ToonTelemetry, Display, TEXT("Creating Toon Telemetry Instance"));

	// Check Instance Data complies with Telemetry Systetm Requirements
	if(!ValidTelemetryInstance(Name, ExtraColumns)) return nullptr;

	// Create Telemetry Instance
	if(const TObjectPtr<UToonTelemetryInstance> TelemetryInstance = NewObject<UToonTelemetryInstance>())
	{
		TelemetryInstance->InitializeTelemetry(GetNewTelemetryID(), Name, ExtraColumns);
		TelemetryInstances.Add(TelemetryInstance);

		UE_LOG(ToonTelemetry, Display, TEXT("Success - Create Telemetry Instance %s"), *Name);
		UE_LOG(ToonTelemetry, Display, TEXT("Finished Toon Telemetry Instance creation"));

		return TelemetryInstance;
	}

	UE_LOG(ToonTelemetry, Error, TEXT("Error - Create Telemetry Instance %s"), *Name);
	UE_LOG(ToonTelemetry, Warning, TEXT("Cancelling Toon Telemetry Instance creation"));

	return nullptr;
}

bool UToonTelemetrySubsystem::ValidTelemetryInstance(const FString& Name, TArray<FString>& ExtraColumns)
{
	// Check File Name is valid
	if (FText Error; !FFileHelper::IsFilenameValidForSaving(Name, Error))
	{
		UE_LOG(ToonTelemetry, Error, TEXT("Error - Instance Name %s validation: %s"), *Name, *Error.ToString());
		UE_LOG(ToonTelemetry, Error, TEXT("Cancelling Toon Telemetry Instance creation"));

		return false;
	}

	UE_LOG(ToonTelemetry, Display, TEXT("Success - Instance Name %s Validation "), *Name);

	UE_LOG(ToonTelemetry, Display, TEXT("Success - SubDirectory %s Validation "), *Name);

	// Check Additional Columns are valid
	ExtraColumns.Insert(UToonTelemetryHelper::GetDefaultColumns(), 0);
	for (const FString& Column : ExtraColumns)
	{
		if (FText Error; !FFileHelper::IsFilenameValidForSaving(Column, Error))
		{
			UE_LOG(ToonTelemetry, Error, TEXT("Error - Invalid Column Name: %s"), *Error.ToString());
			UE_LOG(ToonTelemetry, Error, TEXT("Cancelling Toon Telemetry Instance creation"));

			return false;
		}
	}

	// Insert defualt columns at start of column array
	UE_LOG(ToonTelemetry, Display, TEXT("Success - Column Validation "));

	return true;
}
