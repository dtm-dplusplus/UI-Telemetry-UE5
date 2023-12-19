// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ToonActivatableWidget.h"
#include "ToonActivatableWidgetStack.h"
#include "ToonLayerWidget.generated.h"


// Struct which stores the layer ID and name
// Use this instead of TPair<int,FString> as pairs cannot be returned to blueprint
// In future implementations this can be built out to hold more layer properties
USTRUCT(BlueprintType)
struct FToonLayerData
{
	GENERATED_BODY()

public:

	FToonLayerData(){}

	// Init Layer Struct properties
	void InitLayerData(FString Name, const int ID)
	{
		LayerID = ID;
		LayerName = Name;
	}

	// This layer's Unique ID, set by the UI subsytem.
	// This will not correspond with the UI layer stack pointer index. Which is adjusted dynamically throughout the games runtime.
	// Use GetLayerID() and pass this to the layer stack functions for UI functionallity.
	UPROPERTY(BlueprintReadOnly)
	int LayerID;

	// The name of the layer. Set by the layer name argument passed to the Subsystem CreateLayer function.
	// The name is unique to this subsystem and has no effect on UMG or CommonUI functionallity.
	UPROPERTY(BlueprintReadOnly)
	FString LayerName;
};


// The Layer Widget allows widgets to be pushed onto a widget stack. Only the top most widget will be activated.
// When a widget is popped/removed from the top of the stack, the widget beneath it becomes the active widget of the layer.
UCLASS()
class TOONTANKS_API UToonLayerWidget : public UToonActivatableWidget
{
	GENERATED_BODY() 

public:
	// Setup the layer properites
	void InitLayer(FString Name, const int ID);

	// Adds a widget to the layer and activates it.
	// Acts as a wrapper function to CommonUI AddWidget()
	UFUNCTION(BlueprintCallable)
	UToonActivatableWidget* PushWidgetToLayer(TSubclassOf<UToonActivatableWidget> Widget);

	// Removes the topmost (active) widget from the stack
	UFUNCTION(BlueprintCallable)
	void DeactivateWidgetFromLayer();

public:
	// Returns the struct primive that holds the layers properties like Name and ID
	UFUNCTION(BlueprintGetter)
	FToonLayerData GetLayerData() const { return LayerData; }

	// Returns the layer's unique ID which was set by the UI Subsytem upon layer creation
	UFUNCTION(BlueprintGetter)
	int GetLayerID() const { return LayerData.LayerID; }

	// Returns the layer's unique name which was set by the user
	UFUNCTION(BlueprintGetter)
	FString GetLayerName() const { return LayerData.LayerName; }

protected:
	UPROPERTY(BlueprintReadOnly)
	FToonLayerData LayerData;

	// The derived commonUI widget stack onto which widgets are added
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UToonActivatableWidgetStack> LayerStack;
};
