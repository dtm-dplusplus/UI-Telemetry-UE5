// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ToonTelemetryHelper.h"
#include "ToonTelemetryInstance.generated.h"


/**
* Instances of this class represents a csv file, all the data stored here will be exported to a csv file
* There will be multiple instances of this class, each instance will be a different csv file based on the type of data
* The data will be stored in a list of FToonTelemetryEvent, each event will be a row in the csv file
*/
UCLASS(BlueprintType)
class TOONTANKS_API UToonTelemetryInstance : public UObject
{
	GENERATED_BODY()

public:
	/**
	 * Default Constructor. Values -1 indicate this instance has not been initialized.
	 */
	UToonTelemetryInstance()
	{
		InstanceID = -1;
		FileDir = "";
		FilePath = "";
		FileName = "";
		FileColumns = {};
	}

	/**
	* Sets the key attributes for the telemetry instance
	* @args NewID	- The Unique ID of this instance, set by the subsystem
	* @args Name	- The Unique Name of ths instance, set by the user
	* @args Date	- The date of creation, written to the file name
	* @args SubDir	- Optional Subdirectory name. Useful if you have lots of telemetry instances
	*/
	bool InitializeTelemetry(const int NewID, const FString& Name,
	                         const TArray<FString> CustomColumns);

	

	UFUNCTION(BlueprintCallable)
	void SaveEvent(const FString& EventName, const FString& EventCategory,
		const TArray<FString>& CustomColumnValues);

protected:
	/** Unique Telemetry Instance InstanceID */
	UPROPERTY(BlueprintReadOnly)
	int InstanceID;

	/**
	* Name of the csv file to be generted by the telemetry manager
	*/
	UPROPERTY(BlueprintReadOnly)
	FString FileName;

	/**
	*
	*/
	UPROPERTY(BlueprintReadOnly)
	FString FileDir;

	/**
	* 
	*/
	UPROPERTY(BlueprintReadOnly)
	FString FilePath;

	/**
	* The Column names used in this instances CSV File
	*/
	UPROPERTY(BlueprintReadOnly)
	TArray<FString> FileColumns;

private:
	bool WriteRowToFile(const FString& Row) const
	{
		// Write Row To File
		if (!FFileHelper::SaveStringToFile(Row, *FilePath,
			FFileHelper::EEncodingOptions::AutoDetect,
			&IFileManager::Get(),
			FILEWRITE_Append)
			)
		{
			UE_LOG(ToonTelemetry, Error, TEXT("Error - Write to CSV File %s"), *FilePath);
			return false;
		}

		return true;
	}
};
