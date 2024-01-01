// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ToonTelemetryHelper.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(ToonTelemetry, Log, All);

/**
* Telemetry helper is a function library for the telemetry subsystem
* Both the Telemetry subsystem and Telemetry Instance classes depend on this helper library
* It provides useful string formatting functions which are also accesible in blueprint
*/
UCLASS()
class TOONTANKS_API UToonTelemetryHelper : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	* Initializes the helper. Sets the session date
	* This is called by the Telemetry subsystem at runtime
	*/
	static void InitializeTelemetryDirectory();

	/**
	* @param List		- List of Strings to seperate by comma
	* @param bNewLine	- Add a new line char to end of string?
	* @return			- list of strings to a csv string
	*/
	UFUNCTION(BlueprintPure)
	static FString GetStringListToCSVString(TArray<FString> List, const bool bNewLine = true)
	{
		FString CSVString;

		for (size_t L{ 0 }; L < List.Max() - 1; L++) CSVString += List[L] + ",";
		CSVString += List.Last();
		if (bNewLine) CSVString += "\n";

		return CSVString;
	}

	/**
	* @param Vector - The vector to convert
	* @return		- array of vecter elements formatted as strings
	*/
	UFUNCTION(BlueprintPure)
	static TArray<FString> GetVectorToStringList(const FVector& Vector)
	{
		return { FString::SanitizeFloat(Vector.X) , FString::SanitizeFloat(Vector.X), FString::SanitizeFloat(Vector.Z) };
	}

	/**
	 * @param DateTime	- FDateTime to convert
	 * @param bFileName	- Use a format suitable for file name saving
	 * @return			- FDateTime formatted as a string
	 */
	UFUNCTION(BlueprintPure)
	static FString GetDateTimeToString(const FDateTime DateTime, const bool bFileName = false)
	{
		const FString Day = FString::FromInt(DateTime.GetDay());
		const FString Month = FString::FromInt(DateTime.GetMonth());
		const FString Year = FString::FromInt(DateTime.GetYear()).RightChop(2);
		const FString Hour = FString::FromInt(DateTime.GetHour());
		const FString Minute = FString::FromInt(DateTime.GetMinute());
		const FString Second = FString::FromInt(DateTime.GetSecond());

		if (bFileName) return Day + "-" + Month + "-" + Year + "_" + Hour + "-" + Minute + "-" + Second;
		return Day + "/" + Month + "/" + Year + " " + Hour + ":" + Minute + ":" + Second; 
	}

	/**
	 * @param bFileName - Use a format suitable for file name saving
	 * @return			- Current Time Formatted as a string
	 */
	UFUNCTION(BlueprintPure)
	static FString GetDateTimeNowToString(const bool bFileName = false) { return GetDateTimeToString(FDateTime::Now(), bFileName); }

	/**
	* Columns which are added to instance CSV's by default
	* Custom columns are added after default columns
	* TimeStamp - Time event occurred
	* EventName -  Name of the event
	* EventCategory - Category of the event
	*/
	UFUNCTION(BlueprintPure)
	static TArray<FString> GetDefaultColumns() { return { "TimeStamp", "EventName", "EventCategory" }; }

	/**
	 * @return	- Telemetry Save Directory for this session 
	 */
	UFUNCTION(BlueprintPure)
	static FString GetTelemetryDirectory() { return FPaths::ProjectSavedDir() + "/Telemetry/" + SessionDate + "/"; }

public:
	/**
	 * Creates a CSV file with given path name
	 *
	 * @param FilePath	- Name of file path to create
	 * @return			- Outcome of create operation
	 */
	UFUNCTION(BlueprintCallable)
	static bool CreateCSVFile(const FString& FilePath)
	{
		// Create File
		if (!FFileHelper::SaveStringToFile(nullptr, *FilePath))
		{
			UE_LOG(ToonTelemetry, Error, TEXT("Error - Create CSV File %s"), *FilePath);
			return false;
		}

		UE_LOG(ToonTelemetry, Display, TEXT("Success - Create CSV File %s"), *FilePath);
		return true;
	}

	/**
	 * Write a row to CSV File
	 *
	 * @param Row			- The String row to write
	 * @param FilePath		- The path of the file to write to
	 * @param bAppendToFile - Should append or overwrite file
	 * @return				- Outcome of write operation
	 */
	UFUNCTION(BlueprintCallable)
	static bool WriteRowToFile(const FString& Row, const FString& FilePath, const bool bAppendToFile = true)
	{
		// Overwrite Row To File
		if(!bAppendToFile)
		{
			if (!FFileHelper::SaveStringToFile(Row, *FilePath))
			{
				UE_LOG(ToonTelemetry, Error, TEXT("Error - Write to CSV File %s"), *FilePath);
				return false;
			}
			return true;
		}

		// Append Row To File
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
private:
	/**
	* The date set at runtime. Used to set session telemetry save directory
	* Telemtry Instances created during this session will save to the dated directory
	*/
	static FString SessionDate;
};
