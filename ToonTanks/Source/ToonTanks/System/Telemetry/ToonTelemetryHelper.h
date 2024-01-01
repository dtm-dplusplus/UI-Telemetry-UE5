// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ToonTelemetryHelper.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(ToonTelemetry, Log, All);


/**
 * 
 */
UCLASS()
class TOONTANKS_API UToonTelemetryHelper : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UToonTelemetryHelper(){}

	/**
	 * Converts a list of strings to a csv string
	 * @param List
	 * @param bNewLine
	 * @return
	 */
	UFUNCTION(BlueprintCallable)
	static FString GetListToCSVString(TArray<FString> List, const bool bNewLine = true)
	{
		FString CSVString;

		for (size_t L{ 0 }; L < List.Max() - 1; L++) CSVString += List[L] + ",";
		CSVString += List.Last();
		if (bNewLine) CSVString += "\n";

		return CSVString;
	}

	/**
	* 
	* @param Vector - The vector to convert
	* @return		- Each XYZ unit converted into element in string list
	*/
	UFUNCTION(BlueprintCallable)
	static TArray<FString> GetVectorToStringList(const FVector Vector)
	{
		return { FString::SanitizeFloat(Vector.X) , FString::SanitizeFloat(Vector.X), FString::SanitizeFloat(Vector.Z) };
	}

	/**
	 * Converts a FDateTime to a string
	 * @param DateTime
	 * @param bFileName
	 * @return
	 */
	UFUNCTION(BlueprintCallable)
	static FString GetDateTimeToString(const FDateTime DateTime, const bool bFileName = false)
	{
		const FString Day = FString::FromInt(DateTime.GetDay());
		const FString Month = FString::FromInt(DateTime.GetMonth());
		const FString Year = FString::FromInt(DateTime.GetYear()).RightChop(2);
		const FString Hour = FString::FromInt(DateTime.GetHour());
		const FString Minute = FString::FromInt(DateTime.GetMinute());
		const FString Second = FString::FromInt(DateTime.GetSecond());

		if (!bFileName) return Day + "/" + Month + "/" + Year + " " + Hour + ":" + Minute + ":" + Second;

		return Day + "-" + Month + "-" + Year + "_" + Hour + "-" + Minute + "-" + Second;
	}

	UFUNCTION(BlueprintCallable)
	static FString GetDateTimeNowToString(const bool bFileName = false) { return GetDateTimeToString(FDateTime::Now(), bFileName); }

	static TArray<FString> GetDefaultColumns() { return { "TimeStamp", "EventName", "EventCategory" }; }

	/**
	 * 
	 * @return	- Telemetry Save Directory for this session 
	 */
	UFUNCTION(BlueprintCallable)
	static FString GetTelemetryDirectory() { return FPaths::ProjectSavedDir() + "/Telemetry/" + TelemetrySessionDate + "/"; }

private:
	/** The date set at runtime. Used to set session telemetry save directory*/
	static FString TelemetrySessionDate;
};
