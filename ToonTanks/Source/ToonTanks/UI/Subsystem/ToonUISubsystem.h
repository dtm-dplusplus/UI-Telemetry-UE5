// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ToonTanks/UI/ToonLayerWidget.h"
#include "ToonUISubsystem.generated.h"

class UToonActivatableWidget;

/**
 * UI made easy with the Toon UI Subsytem
 * The Toon UI Subsytem acts as a comprehensive wrapper for UMG and CommonUI
 * Create layers and add widgets simply by layer reference or via the subsytem PushByAttribute functoons
 */
UCLASS()
class TOONTANKS_API UToonUISubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	/**
	* Creates a Layer which widgets can be added to.
	* Once initialized layer data attributes cannot be changed
	*
	* @param Widget		- The Widget Blueprint Toon Layer
	* @param Name		- The Name to set for the Layer.
	* @return			- UToonLayerWidget pointer of new layer
	* @return			- nullptr. If Layer creation failed
	*/
	UFUNCTION(BlueprintCallable)
	UToonLayerWidget* CreatLayerWidget(TSubclassOf<UToonLayerWidget> Widget, FString Name);

	/**
	* @return	- layer pointer. If a matching layer name can be found
	* @return	- nullptr if no match found
	*/
	UFUNCTION(BlueprintCallable)
	UToonLayerWidget* GetLayerByName(const FString LayerName)
	{
		const FString LayerLowerCase = LayerName.ToLower();

		for (UToonLayerWidget* Layer : LayerList)
			if (Layer->GetLayerName().ToLower() == LayerLowerCase) return Layer;

		return nullptr;
	}

	/**
	* @return	- layer pointer. If a matching layer ID can be found
	* @return	- nullptr if no match found
	*/
	UFUNCTION(BlueprintCallable)
	UToonLayerWidget* GetLayerByID(const int LayerID)
	{
		for (UToonLayerWidget* Layer : LayerList)
			if (Layer->GetLayerID() == LayerID) return Layer;

		return nullptr;
	}

	/**
	* Add a widget to the corresponding layer by name (case insensitve)
	* @param Widget		- The Widget Blueprint
	* @param Name		- The Name of the widget.
	*
	* @return			- UToonActivatableWidget pointer of new widget
	* @return			- nullptr. If Layer creation failed
	*/
	UFUNCTION(BlueprintCallable)
	UToonActivatableWidget* PushWidgetByLayerName(const TSubclassOf<UToonActivatableWidget> Widget, const FString Name)
	{
		if (UToonLayerWidget* Layer = GetLayerByName(Name))
		{
			if (UToonActivatableWidget* NewWidget = Layer->PushWidgetToLayer(Widget))
				return NewWidget;
		}

		UE_LOG(LogTemp, Warning, TEXT("Layer could not be found. Failed to add widget"))
		return nullptr;
	}

	

	/**
	* Deactivates the layer with matching name
	* The name is not case sensitive
	* @param Name	- The Name of the Layer to remove.
	* @return		- True. If remove successful
	* @return		- False. If remove failed
	*/
	UFUNCTION(BlueprintCallable)
	bool RemoveLayerByName(const FString Name)
	{
		if (const TObjectPtr<UToonLayerWidget> Layer = GetLayerByName(Name))
			return RemoveLayer(Layer);

		UE_LOG(LogTemp, Warning, TEXT("Failed to delete layer widget: Layer could not be found. "))
			return false;
	}

	/**
	* Deactivates the layer with matching ID
	* @param ID	- The ID of the Layer to remove.
	* @return		- True. If remove successful
	* @return		- False. If remove failed
	*/
	UFUNCTION(BlueprintCallable)
	bool RemoveLayerByID(const int ID)
	{
		if (const TObjectPtr<UToonLayerWidget> Layer = GetLayerByID(ID))
			return RemoveLayer(Layer);

		UE_LOG(LogTemp, Warning, TEXT("Failed to delete layer widget: Layer could not be found."))
			return false;
	}

	/**
	* Remove the active widget from the corresponding layer by name (case insensitve)
	* @param Name		- The Name of the layer.
	*
	* @return			- true. If Layer deleted succsessfully
	*/
	UFUNCTION(BlueprintCallable)
	bool RemoveActiveWidgetByLayerName(const FString Name)
	{
		if (const TObjectPtr<UToonLayerWidget> Layer = GetLayerByName(Name))
		{
			Layer->RemoveActiveWidget();
			return true;
		}

		UE_LOG(LogTemp, Warning, TEXT("Layer could not be found. Failed to remove widget"))
			return false;
	}

	/**
	* Remove the active widget from the corresponding layer by ID
	* @param ID		- The ID of the layer.
	*
	* @return		- true. If Layer deleted succsessfully
	*/
	UFUNCTION(BlueprintCallable)
	bool RemoveActiveWidgetByLayerID(const int ID)
	{
		if (const TObjectPtr<UToonLayerWidget> Layer = GetLayerByID(ID))
		{
			Layer->RemoveActiveWidget();
			return true;
		}

		UE_LOG(LogTemp, Warning, TEXT("Layer could not be found. Failed to remove widget"))
			return false;
	}


public:
	/**
	* @return all of the active layer pointers
	*/
	UFUNCTION(BlueprintCallable)
	TArray<UToonLayerWidget*> GetAllLayers() { return LayerList; }

	/**
	* @return all of the layer data structs from active layers
	*/
	UFUNCTION(BlueprintCallable)
	TArray<FToonLayerData> GetAllLayerData()
	{
		TArray<FToonLayerData> LayerDataStructs;

		for (const TObjectPtr<UToonLayerWidget> Layer : LayerList)
			LayerDataStructs.Add(Layer->GetLayerData());

		return LayerDataStructs;
	}

	/**
	* @return	- list of the active layer names
	*/
	UFUNCTION(BlueprintCallable)
	TArray<FString> GetAllLayerNames()
	{
		TArray<FString> LayerNames;

		for (const TObjectPtr<UToonLayerWidget> Layer : LayerList)
			LayerNames.Add(Layer->GetLayerName());

		return LayerNames;
	}

	/**
	* @return	- list of layer IDs.
	*/
	UFUNCTION(BlueprintCallable)
	TArray<int> GetAllLayerIDs()
	{
		TArray<int> LayerIDs;

		for (const TObjectPtr<UToonLayerWidget> Layer : LayerList) { LayerIDs.Add(Layer->GetLayerID()); }

		return LayerIDs;
	}

private:

	/**
	* Layer ID Counter. This is used to assign new layers unique IDs
	* Its value is incremented in CreatLayerWidget() when a user calls this function
	*/
	int LayerIDCount;

	/**
	 * Creates a new layer ID for 
	 * @return	- Telemetry ID 
	 */
	int GetNewLayerID() { return LayerIDCount++; }

	/**
	* List of UToonLayerWidget UI layers.
	* When layers are created in CreatLayerWidget() they are added to this
	*/
	TArray<TObjectPtr<UToonLayerWidget>> LayerList;

	/**
	* Removes layer from layer list
	* @args Layer	- Layer to remove
	* @return		- True. if removed successfully
	*/
	bool RemoveLayer(UToonLayerWidget* Layer)
	{
		Layer->DeactivateLayer();
		return static_cast<bool>(LayerList.RemoveSingle(Layer));
	}
};