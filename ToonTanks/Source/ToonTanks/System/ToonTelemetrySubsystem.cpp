// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTelemetrySubsystem.h"

bool UToonTelemetryInstance::InitializeTelemetry(const int NewID, const FString& Name, const FString& Date,
                                                 const FString& SubDir, TArray<FString> Columns)
{
	// Set InstanceID
	InstanceID = NewID;

	// Set File Name
	FileName = Name + " " + Date;

	// Set File Sub Directory
	FileSubDir = SubDir;

	// Set Friendly Name
	FriendlyName = Name;

	// Set FileColumns
	FileColumns = { "TimeStamp", "EventCategory", "EventName" };
	for (FString Column : Columns) FileColumns.Add(Column);

	// Attempt CSV file creation
	if(!CreateCSVFile(FileName, FileColumns, "dir?"))
	{
		UE_LOG(LogTemp, Error, TEXT("UToonTelemetrySubsystem: Failed to create Telemetry Instance CSV File"));
		return false;
	}

	UE_LOG(LogTemp, Display, TEXT("UToonTelemetrySubsystem: created Telemetry Instance CSV File successfully"));

	return true;
}

void UToonTelemetryInstance::SaveTelemetryEvent(const FString& EventName, const FString& EventCategory, const FDateTime EventTime)
	
{
	// Write straight to file instead of saving to array
	//FToonTelemetryEvent TelemetryEvent;
	//TelemetryEvent.InitializeTelmetryEvent(EventTime.ToString(), EventCategory, EventName);
	//TelemetryEvents.Add(TelemetryEvent);
}



void UToonTelemetrySubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	TelemetrySaveDir = FPaths::ProjectSavedDir() + "/Telemetry/";
	TelemetryIDCount = 0;

	// Check Telemetry Directory Exists. If not, create it.
	if (IPlatformFile& FM = FPlatformFileManager::Get().GetPlatformFile(); !FM.DirectoryExists(*TelemetrySaveDir))
	{
		UE_LOG(LogTemp, Warning, TEXT("TelemetrySubsystem: Telemetry Directory Does not exist"));

		if (!FM.CreateDirectory(*TelemetrySaveDir))
		{
			UE_LOG(LogTemp, Warning, TEXT("TelemetrySubsystem: Telemetry Directory was created"));
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("TelemetryManager: Telemetry Directory was not created"));
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("UToonTelemetrySubsystem Initialised"))

	// Create Master Telemetry Instance at index 0
	CreateTelemetryInstance("Master", TODO);
	SaveTelemetryEvent("UToonTelemetrySubsystem Initialised", "Telemetry", FDateTime::Now());
}

void UToonTelemetrySubsystem::Deinitialize()
{

	SaveTelemetryEvent("UToonTelemetrySubsystem Shutting Down", "Telemetry", FDateTime::Now());


	if(!TelemetryInstances.IsEmpty())
	{
		for (UToonTelemetryInstance* Instance : TelemetryInstances)
		{
			if(Instance)
				ExportTelemetryInstance(Instance);
			else
				UE_LOG(LogTemp, Warning, TEXT("No Telemetry Instances found"))
		}
	}
	

	UE_LOG(LogTemp, Warning, TEXT("UToonTelemetrySubsystem Deinitialised"))

	Super::Deinitialize();

}

UToonTelemetryInstance* UToonTelemetrySubsystem::CreateTelemetryInstance(const FString& Name, FString SubDir)
{
	// Check File Name is valid
	if(FText Error; !FFileHelper::IsFilenameValidForSaving(Name,Error))
	{
		UE_LOG(LogTemp, Warning, TEXT("UToonTelemetrySubsystem: Invalid Instance Name: %s"), *Error.ToString());

		return nullptr;
	}

	// Check SubDirectory is valid
	if(SubDir != "")
	{
		if (FText Error; !FFileHelper::IsFilenameValidForSaving(Name, Error))
		{
			UE_LOG(LogTemp, Warning, TEXT("UToonTelemetrySubsystem: Invalid SubDirectory Instance: %s"), *Error.ToString());
			UE_LOG(LogTemp, Warning, TEXT("UToonTelemetrySubsystem: Saving to Default directory instead"));

			// Reset to default directory
			SubDir = "";
		}
	}

	// Create Telemetry Instance
	if(const TObjectPtr<UToonTelemetryInstance> TelemetryInstance = NewObject<UToonTelemetryInstance>())
	{
		TelemetryInstance->InitializeTelemetry(GetNewTelemetryID(), Name, GetDateTimeToString(), SubDir, TODO);
		TelemetryInstances.Add(TelemetryInstance);

		UE_LOG(LogTemp, Warning, TEXT("UToonTelemetrySubsystem: Created Telemetry Instance: %s"), *Name);

		return TelemetryInstance;
	}

	UE_LOG(LogTemp, Error, TEXT("UToonTelemetrySubsystem: Failed to create Telemetry Instance"));

	return nullptr;
}