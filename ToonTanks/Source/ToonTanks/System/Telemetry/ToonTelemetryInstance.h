// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	UToonTelemetryInstance();

	/**
	* Sets the key attributes for the telemetry instance
	*
	* @args NewID			- The Unique ID of this instance, set by the subsystem
	* @args Name			- The Unique Name of ths instance, set by the user
	* @args CustomColumns	- Optional Custom columns provided by the user
	* @return				- true if initialization successful
	*/
	bool InitializeInstance(const int NewID, const FString& Name, const TArray<FString>& CustomColumns);

	/**
	* Saves event data to the instance's CSV file
	* Custom column data must be passed as a TArray
	*
	* @param EventName			- Name of the event
	* @param EventCategory		- Category of the event
	* @param CustomColumnData	- Aditional data from the event.
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure = false, meta = (AutoCreateRefTerm = "CustomColumnData"))
	void SaveEvent(const FString& EventName, const FString& EventCategory, const TArray<FString>& CustomColumnData) const;

protected:
	/** Unique Telemetry Instance InstanceID */
	UPROPERTY(BlueprintReadOnly)
	int InstanceID;

	/**
	* Name of the instance's CSV file
	*/
	UPROPERTY(BlueprintReadOnly)
	FString FileName;

	/**
	* The directory the instance's CSV file is located in
	*/
	UPROPERTY(BlueprintReadOnly)
	FString FileDir;

	/**
	* The full path to the instance's CSV file
	*/
	UPROPERTY(BlueprintReadOnly)
	FString FilePath;

	/**
	* The Column names used in this instance's CSV file
	* This can include custom columns set by the user
	*/
	UPROPERTY(BlueprintReadOnly)
	TArray<FString> FileColumns;
};
