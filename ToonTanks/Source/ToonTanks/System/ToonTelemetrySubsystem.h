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
	UToonTelemetryInstance();

	/**
	* Sets the key attributes for the telemetry instance
	* @args NewID	- The Unique ID of this instance, set by the subsystem
	* @args Name	- The Unique Name of ths instance, set by the user
	* @args Date	- The date of creation, written to the file name
	* @args SubDir	- Optional Subdirectory name. Useful if you have lots of telemetry instances
	*/
	UFUNCTION(BlueprintCallable)
	void InitializeTelemetry(const uint8 NewID, const FString& Name, const FString& Date, const FString& SubDir = "");

	/**
	* 
	* @param EventName 
	* @param EventCategory 
	* @param EventTime 
	*/
	UFUNCTION(BlueprintCallable)
	void CreateTelemetryEvent(const FString& EventName, const FString& EventCategory, const FDateTime EventTime);
	/**
	* 
	* @return 
	*/
	UFUNCTION(BlueprintGetter)
	uint8 GetTelemetryID() const { return InstanceID; }

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
	uint8 InstanceID;

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
	 * 
	 * @param EventName 
	 * @param EventCategory 
	 * @param EventTime 
	 */
	UFUNCTION(BlueprintCallable)
	void SaveTelemetryEvent(const FString& EventName, const FString& EventCategory, const FDateTime EventTime);

	/**
	 * 
	 * @param Name 
	 * @return 
	 */
	UFUNCTION(BlueprintCallable)
	UToonTelemetryInstance* CreateTelemetryInstance(const FString& Name);

	/**
	 * 
	 * @param TelemeteryInstance 
	 * @return 
	 */
	UFUNCTION(BlueprintCallable)
	bool ExportTelemetryInstance(UToonTelemetryInstance* TelemeteryInstance);

	/**
	 * Converts the Telemetry to a csv string
	 * @param TelemeteryInstance 
	 * @return 
	 */
	UFUNCTION(BlueprintGetter)
	FString CreateStringFromTelemeteryInstance(UToonTelemetryInstance* TelemeteryInstance);

	/**
	 * 
	 * @param FileContent 
	 * @param FileName 
	 * @param FileSubDir 
	 * @return 
	 */
	UFUNCTION(BlueprintCallable)
	bool CreateCSVFile(const FString& FileContent, const FString& FileName, const FString& FileSubDir = "") const;

	/**
	 * Converts a FDateTime to a string
	 * @param DateTime 
	 * @param bFileFormat 
	 * @return 
	 */
	UFUNCTION(BlueprintGetter)
	FString GetDateTimeToString(FDateTime DateTime, bool bFileFormat = false);

	/**
	 * Converts a list of strings to a csv string
	 * @param List 
	 * @return 
	 */
	UFUNCTION(BlueprintGetter)
	FString GetListToCSVString(TArray<FString> List);

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
	uint8 TelemetryIDCount;
	/** */
	TArray<TObjectPtr<UToonTelemetryInstance>> TelemetryInstances;

private:
	/** */
	uint8 GetNewTelemetryID() { return TelemetryIDCount++; }
};