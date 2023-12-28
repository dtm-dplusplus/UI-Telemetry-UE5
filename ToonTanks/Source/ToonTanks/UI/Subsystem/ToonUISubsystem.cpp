// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonUISubsystem.h"

void UToonUISubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	LayerIDCount = 0;
}

UToonLayerWidget* UToonUISubsystem::CreatLayerWidget(const TSubclassOf<UToonLayerWidget> Widget, const FString Name)
{
	// Check Layer with name does not already exists
	if(GetLayerByName(Name)) 
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to CreatLayerWidget. A layer with this name already exists"))
		return nullptr;
	}

	// Create New Toon Layer Widget
	if(UToonLayerWidget* NewLayerWidget = CreateWidget<UToonLayerWidget>(GetWorld(), Widget))
	{
		// Set Layer properties. The ID is incremented here, ready for the next layer creation
		NewLayerWidget->ActivateLayer(Name, LayerIDCount++);

		// Add the new layer to the subsytem layer list
		LayerList.Add(NewLayerWidget);

		// Return a reference to the blueprint
		return NewLayerWidget; 
	}
	
	UE_LOG(LogTemp, Error, TEXT("Failed to CreatLayerWidget. Create Widget cast failed"))

	return nullptr;
}