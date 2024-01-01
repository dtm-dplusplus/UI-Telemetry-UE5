// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ToonTelemetrySubsystem.generated.h"


class UToonTelemetryInstance;

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
	 * @param ExtraColumns	- Optional sub-folder. Useful if there are lots of telemetry instances
	 * @return			- Pointer to the new telemetry instance. Nullptr if failed to create
	 */
	UFUNCTION(BlueprintCallable, meta = (AutoCreateRefTerm = "ExtraColumns"))
	UToonTelemetryInstance* CreateTelemetryInstance(const FString& Name, TArray<FString> ExtraColumns);


protected:

	/** The list of active Telemetry Instances */
	UPROPERTY(BlueprintReadOnly)
	TArray<TObjectPtr<UToonTelemetryInstance>> TelemetryInstances;

private:
	/** The Number of Telemetry Instance Created. Used to assign unique IDs */
	int TelemetryIDCount;

	/** Creates a new telemetry instance ID and increments the counter */
	int GetNewTelemetryID() { return TelemetryIDCount++; }

	static bool ValidTelemetryInstance(const FString& Name, TArray<FString>& ExtraColumns);
};