// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ToonUISubsystem.generated.h"

class UToonActivatableWidget;
class UToonLayerWidget;

UCLASS()
class TOONTANKS_API UToonUISubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Deinitialize() override;
	
	// Creates a UI Layer which widgets can be added to
	// Once initialized the layer name cannot be changed
	// Returns null if a matching layer name already exists in the list 
	UFUNCTION(BlueprintCallable)
	UToonLayerWidget* CreatLayerWidget(TSubclassOf<UToonLayerWidget> LayerWidget, FString LayerName);

	// Add a widget to the corresponding layer by name (case insensitve)
	UFUNCTION(BlueprintCallable)
	UToonActivatableWidget* PushWidgetByLayerName(TSubclassOf<UToonActivatableWidget> Widget, FString LayerName);

	// Deactivates the layer with macthing name from the layer list
	UFUNCTION(BlueprintCallable)
	bool RemoveLayerByName(FString LayerName);

	UFUNCTION(BlueprintCallable)
	bool RemoveLayerByID(int ID);

	// Returns a layer pointer if a macthing layer name can be found in the list
	UFUNCTION(BlueprintCallable)
	UToonLayerWidget* GetLayerByName(FString LayerName);

	// Returns a layer pointer if a macthing layer name can be found in the list
	UFUNCTION(BlueprintCallable)
	UToonLayerWidget* GetLayerByID(int LayerID);
	// Returns a list of layer IDs and corresponding name
	UFUNCTION(BlueprintCallable)
	TArray<struct FToonLayerData> GetAllLayerData();

	// Returns a list of the active layer names
	UFUNCTION(BlueprintCallable)
	TArray<FString> GetAllLayerNames();

	// Returns the list of layer IDs.
	// The element index directly corresponds to the layer list element indexes
	TArray<int> GetAllLayerIDs();

	

private:

	// Layer ID Counter. This is used to assign new layers unique IDs
	// Its value is incremented in CreatLayerWidget() when a user calls this function
	int LayerIDCount;

	// List of UI layers. When layers are created in CreatLayerWidget() they are added to this
	TArray<TObjectPtr<UToonLayerWidget>> LayerList;
};