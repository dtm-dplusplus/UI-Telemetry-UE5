// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ToonTelemetrySubsystem.generated.h"

/**
* This is the struct that will be used to store the data for each event
*/
USTRUCT(BlueprintType)
struct FToonTelemetryEvent
{
	GENERATED_USTRUCT_BODY()

	FToonTelemetryEvent() {}

	/**
	 * Sets the event struct attributes
	 * @param Time		- Time event occured
	 * @param Category  - Type of event. Useful for filtering in CSV file
	 * @param Name		- Name of the event.
	 */
	void InitializeTelmetryEvent(const FString& Time, const FString& Category, const FString& Name)
	{
		TimeStamp = Time;
		EventCategory = Category;
		EventName = Name;
	}

	/** Time the event occured (String Format)*/
	UPROPERTY()
	FString TimeStamp;

	/** Category of the event being logged */
	UPROPERTY()
	FString EventCategory;

	/** Name of the telemetry event being logged */
	UPROPERTY()
	FString EventName;
};

/**
 * The default instances created by the substem. Accessible in Blueprint
 */
UENUM(BlueprintType)
enum class EToonTelemetryDefaultInstance : uint8 {
	TM_INSTANCE_MASTER       UMETA(DisplayName = "Master"),
	TM_INSTANCE_LOCATION     UMETA(DisplayName = "Location"),
	TM_INSTANCE_SUBSYSTEM    UMETA(DisplayName = "Subsystem"),
};

/**
* Instances of this class represents a csv file, all the data stored here will be exported to a csv file
* There will be multiple instances of this class, each instance will be a different csv file based on the type of data
* The data will be stored in a list of FToonTelemetryEvent, each event will be a row in the csv file
*/
UCLASS(BlueprintType)
class UToonTelemetryInstance : public UObject
{
	GENERATED_BODY()

public:
	
	UToonTelemetryInstance()
	{
		InstanceID = 0;
		FriendlyName = "Telemetry";
		FileName = "Telemetry";
		FileSubDir = "";
		Columns.Add("TimeStamp, Category, Event");
		TelemetryEvents = TArray<FToonTelemetryEvent>();
	}

	/**
	* Sets the key attributes for the telemetry instance
	* @args NewID	- The Unique ID of this instance, set by the subsystem
	* @args Name	- The Unique Name of ths instance, set by the user
	* @args Date	- The date of creation, written to the file name
	* @args SubDir	- Optional Subdirectory name. Useful if you have lots of telemetry instances
	*/
	UFUNCTION(BlueprintCallable)
	void InitializeTelemetry(const int NewID, const FString& Name, const FString& Date, const FString& SubDir = "");
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

	/**
	* 
	* @param EventName 
	* @param EventCategory 
	* @param EventTime 
	*/
	void CreateTelemetryEvent(const FString& EventName, const FString& EventCategory, const FDateTime EventTime)
	{
		FToonTelemetryEvent TelemetryEvent;
		TelemetryEvent.InitializeTelmetryEvent(EventTime.ToString(), EventCategory, EventName);
		TelemetryEvents.Add(TelemetryEvent);
	}

	bool CreateCSVFile(const FString& FileName, const FString& FileColumns, const FString& FileSaveDir) const
	{
		// Create and write to CSV File
		if (!FFileHelper::SaveStringToFile(FileColumns, *FString(FileSaveDir + FileName + ".csv")))
		{
			UE_LOG(LogTemp, Error, TEXT("TelemetryManager: CSV File was not created"));
			return false;
		}

		UE_LOG(LogTemp, Warning, TEXT("TelemetryManager: CSV File was created"));

		return true;
	}
	/**
	* 
	* @return 
	*/
	UFUNCTION(BlueprintGetter)
	int GetTelemetryID() const { return InstanceID; }

	/**
	* 
	* @return 
	*/
	UFUNCTION(BlueprintGetter)
	FString GetFileName() { return FileName; }

	/**
	*
	* @return
	*/
	UFUNCTION(BlueprintGetter)
	FString GetFriendlyName() const { return FriendlyName; }

	/**
	*
	* @return
	*/
	UFUNCTION(BlueprintGetter)
	TArray<FString> GetColumns() { return Columns; }

	/**
	*
	* @return
	*/
	UFUNCTION(BlueprintGetter)
	TArray<FToonTelemetryEvent> GetEvents() { return TelemetryEvents; }
	
protected:
	/** Unique Telemetry Instance InstanceID */
	int InstanceID;

	/** User Friendly File Name.
	* When generating the csv file, date and time will be appended to the file name
	*/
	FString FriendlyName;

	/**
	* Name of the csv file to be generted by the telemetry manager
	*/
	FString FileName;

	/**
	* The subdirectry if the user wants to save the file in a subdirectory. null by default
	*/
	FString FileSubDir;

	/**
	* The subdirectry if the user wants to save the file in a subdirectory. null by default
	*/
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	TArray<FToonTelemetryEvent> TelemetryEvents;

	/**
	* The subdirectry if the user wants to save the file in a subdirectory. null by default
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FString> Columns;
};

/**
 * The Telemetry Substem manages telemetery instances and events.
 * It controls read/write between CSV files and telemetery instances
 */
UCLASS()
class TOONTANKS_API UToonTelemetrySubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	
	/**
	 * Creates a telemetry instance and corresponding CSV file which events can be saved to.
	 * Events saved to this are written directly to the instances CSV file.
	 *
	 * @param Name		- Name of the instance. This name is also used for the CSV file name
	 * @param SubDir	- Optional sub-folder. Useful if there are lots of telemetry instances
	 * @return			- Pointer to the new telemetry instance. Nullptr if failed to create
	 */
	UFUNCTION(BlueprintCallable)
	UToonTelemetryInstance* CreateTelemetryInstance(const FString& Name, FString SubDir = "");

	/**
	 * 
	 * @param TelemeteryInstance 
	 * @return 
	 */
	//UFUNCTION(BlueprintCallable)
	//bool ExportTelemetryInstance(UToonTelemetryInstance* TelemeteryInstance)
	//{
	//	// Create and write to CSV File
	//	if (TelemeteryInstance)
	//	{
	//		if (CreateCSVFile(CreateStringFromTelemeteryInstance(TelemeteryInstance), TelemeteryInstance->GetFileName()))
	//		{
	//			return true;
	//		}
	//	}
	//	else
	//	{
	//		UE_LOG(LogTemp, Error, TEXT("ExportTelemetryInstance: Telemetry Instance not found"));
	//	}

	//	return false;
	//}

	/**
	 * Converts the Telemetry to a csv string
	 * @param TelemeteryInstance 
	 * @return 
	 */
	UFUNCTION(BlueprintGetter)
	static FString CreateStringFromTelemeteryInstance(UToonTelemetryInstance* TelemeteryInstance)
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

	/**
	 * Converts a FDateTime to a string
	 * @param DateTime 
	 * @return 
	 */
	UFUNCTION(BlueprintGetter)
	static FString GetDateTimeToString(const FDateTime DateTime = FDateTime::Now())
	{
		const FString Day = FString::FromInt(DateTime.GetDay());
		const FString Month = FString::FromInt(DateTime.GetMonth());
		const FString Year = FString::FromInt(DateTime.GetYear()).RightChop(2);
		const FString Hour = FString::FromInt(DateTime.GetHour());
		const FString Minute = FString::FromInt(DateTime.GetMinute());
		const FString Second = FString::FromInt(DateTime.GetSecond());

		return Day + "-" + Month + "-" + Year + "_" + Hour + "-" + Minute + "-" + Second;
	}

	/**
	 * Converts a list of strings to a csv string
	 * @param List 
	 * @return 
	 */
	UFUNCTION(BlueprintGetter)
	static FString GetListToCSVString(TArray<FString> List)
	{
		FString CSVString;

		for (size_t L{ 0 }; L < List.Max() - 1; L++) CSVString += List[L] + ",";
		CSVString += List.Last() + "\n";

		return CSVString;
	}

	/**
	 * 
	 * @return 
	 */
	UFUNCTION(BlueprintGetter)
	FString GetTelemetrySaveDir() { return TelemetrySaveDir; }

protected:
	/** */
	FString TelemetrySaveDir;

	/** */
	int TelemetryIDCount;
	/** */
	TArray<TObjectPtr<UToonTelemetryInstance>> TelemetryInstances;

private:
	/** Creates a new telemetry instance ID and increments the counter */
	int GetNewTelemetryID() { return TelemetryIDCount++; }
};