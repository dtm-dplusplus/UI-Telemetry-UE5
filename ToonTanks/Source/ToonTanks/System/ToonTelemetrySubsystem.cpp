// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTelemetrySubsystem.h"

 
void UToonTelemetrySubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	TelemetryIDCount = 0;
	TelemetryInstanceCount = 0;
	TelemetrySaveDir = FPaths::ProjectSavedDir() + "/Telemtry/";

	// Check Directory Exists. If not, create it.
	if (IPlatformFile& FM = FPlatformFileManager::Get().GetPlatformFile(); !FM.DirectoryExists(*TelemetrySaveDir))
	{
		UE_LOG(LogTemp, Warning, TEXT("TelemetryManager: TelemetrySaveDir Directory Does not exist"));

		if (FM.CreateDirectory(*TelemetrySaveDir))
		{
			UE_LOG(LogTemp, Warning, TEXT("TelemetryManager: Directory was created"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("TelemetryManager: Directory was not created"));
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("UToonTelemetrySubsystem Initialised"))

	// Create Master Telemetry Instance at index 0
	CreateTelemetryInstance("Master");
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

void UToonTelemetrySubsystem::SaveTelemetryEvent(const FString& EventName, const FString& EventCategory,
	const FDateTime EventTime)
{
	// Add Event to Master Telemetry Instance
	if(TelemetryInstances[0])
		TelemetryInstances[0]->CreateTelemetryEvent(EventName, EventCategory, EventTime);
	else
		UE_LOG(LogTemp, Error, TEXT("SaveTelemetryEvent: Master Telemetry not found"));
}

UToonTelemetryInstance* UToonTelemetrySubsystem::CreateTelemetryInstance(const FString& Name)
{
	TObjectPtr<UToonTelemetryInstance> TelemetryInstance = NewObject<UToonTelemetryInstance>();
	TelemetryInstance->InitializeTelemetry(GetNewTelemetryID(), Name, GetDateTimeToString(FDateTime::Now(), true));
	TelemetryInstances.Add(TelemetryInstance);

	UE_LOG(LogTemp, Warning, TEXT("UToonTelemetrySubsystem CreateTelemetryInstance"));

	// Return Weak Pointer for Blueprint
	TWeakObjectPtr<UToonTelemetryInstance> WeakTelemetryInstance = TelemetryInstance;

	return TelemetryInstance;
}

bool UToonTelemetrySubsystem::ExportTelemetryInstance(UToonTelemetryInstance* TelemeteryInstance)
{
	// Create and write to CSV File
	if(TelemeteryInstance)
	{
		if (CreateCSVFile(CreateStringFromTelemeteryInstance(TelemeteryInstance), TelemeteryInstance->GetFileName()))
		{
			return true;
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("ExportTelemetryInstance: Telemetry Instance not found"));
	}
	 
	return false;
}

FString UToonTelemetrySubsystem::CreateStringFromTelemeteryInstance(UToonTelemetryInstance* TelemeteryInstance)
{
	// Set First Line to columns
	FString WriteString = GetListToCSVString(TelemeteryInstance->GetColumns()); // Writes columns to first line

	// Write rest of the rows/lines
	// This is hard coded for now, but will be changed to be dynamic.
	// Currently only supports default columns
	for (FToonTelemetryEvent& Entry : TelemeteryInstance->GetEvents())
		WriteString += GetListToCSVString({ Entry.TimeStamp, Entry.EventCategory, Entry.EventName });

	return WriteString;
}

bool UToonTelemetrySubsystem::CreateCSVFile(const FString& FileContent, const FString& FileName, const FString& FileSubDir) const
{
	// Create and write to CSV File
	if (!FFileHelper::SaveStringToFile(FileContent, *FString(TelemetrySaveDir  + FileSubDir + FileName + ".csv")))
	{
		UE_LOG(LogTemp, Error, TEXT("TelemetryManager: CSV File was not created"));
		return false;
	}

	UE_LOG(LogTemp, Warning, TEXT("TelemetryManager: CSV File was created"));

	return true;
}


FString UToonTelemetrySubsystem::GetDateTimeToString(const FDateTime DateTime, const bool bFileFormat)
{
	const FString Day = FString::FromInt(DateTime.GetDay());
	const FString Month = FString::FromInt(DateTime.GetMonth());
	const FString Year = FString::FromInt(DateTime.GetYear()).RightChop(2);
	const FString Hour = FString::FromInt(DateTime.GetHour());
	const FString Minute = FString::FromInt(DateTime.GetMinute());
	const FString Second = FString::FromInt(DateTime.GetSecond());

	// Check Output Format - Files use . and - instead of / and :
	if(!bFileFormat)
		return Day + "/" + Month + "/" + Year + " " + Hour + ":" + Minute + ":" + Second;

	return Day + "-" + Month + "-" + Year + "_" + Hour + "-" + Minute + "-" + Second;
}

FString UToonTelemetrySubsystem::GetListToCSVString(TArray<FString> List)
{
	FString CSVString;

	for (size_t L{ 0 }; L < List.Max() - 1; L++) CSVString += List[L] + ",";
	CSVString += List.Last() + "\n";

	return CSVString;
}






UToonTelemetryInstance::UToonTelemetryInstance()
{
	InstanceID = 0;
	FriendlyName = "Telemetry";
	FileName = "Telemetry";
	FileSubDir = "";
	Columns.Add("TimeStamp, Category, Event");
	TelemetryEvents = TArray<FToonTelemetryEvent>();
}

void UToonTelemetryInstance::InitializeTelemetry(const uint8 NewID, const FString& Name, const FString& Date, const FString& SubDir)
{
	// Set InstanceID
	InstanceID = NewID;

	// Set File Name
	FileName = Name + " " + Date;

	// Set File Sub Directory
	FileSubDir = SubDir;

	// Set Friendly Name
	FriendlyName = Name;

	// Set Columns
	Columns = { "TimeStamp", "EventCategory", "EventName" };
}

void UToonTelemetryInstance::CreateTelemetryEvent(const FString& EventName, const FString& EventCategory,
                                                  const FDateTime EventTime)
{
	FToonTelemetryEvent TelemetryEvent;
	TelemetryEvent.InitializeTelmetryEvent(EventTime.ToString(), EventCategory, EventName);
	TelemetryEvents.Add(TelemetryEvent);
}