// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ToonTelemetrySubsystem.generated.h"

// This is the struct that will be used to store the data for each event
USTRUCT(BlueprintType)
struct FToonTelemetryEvent
{
	GENERATED_USTRUCT_BODY()

public:
	FToonTelemetryEvent() {}
	void InitializeTelmetryEvent(const FString& Time, const FString& Category, const FString& Name)
	{
		TimeStamp = Time;
		EventCategory = Category;
		EventName = Name;
	}

	// Time the event occured
	UPROPERTY()
	FString TimeStamp;

	// Category of the event being logged
	UPROPERTY()
	FString EventCategory;

	// Name of the telemetry event being logged
	UPROPERTY()
	FString EventName;

	// The name of the attribute column and its value
	// TPair<FString, FString> EventAtributes;
};



// This class is essentially a csv file, all the data stored here will be exported to a csv file
// There will be multiple instances of this class, each instance will be a different csv file based on the type of data
// The data will be stored in a list of FToonTelemetryEvent, each event will be a row in the csv file
UCLASS(BlueprintType, Blueprintable)
class UToonTelemetryInstance : public UObject
{
	GENERATED_BODY()

public:
	UToonTelemetryInstance();

	// Sets default values for this actor's properties
	UFUNCTION(BlueprintCallable)
	void InitializeTelemetry(const uint8 NewID, const FString& Name, const FString& Date, const FString& SubDir = "");

	UFUNCTION(BlueprintCallable)
	void CreateTelemetryEvent(const FString& EventName, const FString& EventCategory, const FDateTime EventTime);

	UFUNCTION(BlueprintGetter)
	uint8 GetTelemetryID() const { return InstanceID; }

	UFUNCTION(BlueprintGetter)
	FString GetFileName() { return FileName; }

	UFUNCTION(BlueprintGetter)
	FString GetFriendlyName() const { return FriendlyName; }

	UFUNCTION(BlueprintGetter)
	TArray<FString> GetColumns() { return Columns; }

	UFUNCTION(BlueprintGetter)
	TArray<FToonTelemetryEvent> GetEvents() { return TelemetryEvents; }

	// Link column to the type for data evaluation
	//TMap<FString, USceneComponent> ColumnsMap;

protected:
	// Unique Telemetry Instance InstanceID
	uint8 InstanceID;

	// User Friendly File Name.
	// When generating the csv file, date and time will be appended to the file name
	FString FriendlyName;

	// Name of the csv file to be generted by the telemetry manager
	FString FileName;

	// The subdirectry if the user wants to save the file in a subdirectory. null by default
	FString FileSubDir;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	TArray<FToonTelemetryEvent> TelemetryEvents;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FString> Columns;
};

UCLASS(config = Telemetry)
class TOONTANKS_API UToonTelemetrySubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	UFUNCTION(BlueprintCallable)
	void SaveTelemetryEvent(const FString& EventName, const FString& EventCategory, const FDateTime EventTime);

	UFUNCTION(BlueprintCallable)
	UToonTelemetryInstance* CreateTelemetryInstance(const FString& Name);

	UFUNCTION(BlueprintCallable)
	bool ExportTelemetryInstance(UToonTelemetryInstance* TelemeteryInstance);

	// Converts the Telemetry to a csv string
	UFUNCTION(BlueprintGetter)
	FString CreateStringFromTelemeteryInstance(UToonTelemetryInstance* TelemeteryInstance);

	UFUNCTION(BlueprintCallable)
	bool CreateCSVFile(const FString& FileContent, const FString& FileName, const FString& FileSubDir = "") const;

	// Converts a FDateTime to a string
	UFUNCTION(BlueprintGetter)
	FString GetDateTimeToString(FDateTime DateTime, bool bFileFormat = false);

	// Converts a list of strings to a csv string
	UFUNCTION(BlueprintGetter)
	FString GetListToCSVString(TArray<FString> List);

	UFUNCTION(BlueprintGetter)
	FString GetTelemetrySaveDir() { return TelemetrySaveDir; }



public:
	FString TelemetrySaveDir;

	uint8 TelemetryIDCount;

	TArray<TObjectPtr<UToonTelemetryInstance>> TelemetryInstances;

private:
	uint8 GetNewTelemetryID() { return TelemetryIDCount++; }

};