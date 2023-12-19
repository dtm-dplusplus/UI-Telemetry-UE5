// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonUISubsystem.h"

#include "Engine/GameViewportClient.h"
#include "ToonTanks/UI/ToonLayerWidget.h"

void UToonUISubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	LayerIDCount = 0;
}

void UToonUISubsystem::Deinitialize()
{
	Super::Deinitialize();

}



UToonLayerWidget* UToonUISubsystem::CreatLayerWidget(TSubclassOf<UToonLayerWidget> LayerWidget, FString LayerName)
{
	if(GetLayerByName(LayerName)) 
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to CreatLayerWidget. A layer with this name already exists"))
		return nullptr;
	}

	// Create New Toon Layer Widget
	if(UToonLayerWidget* NewLayerWidget = CreateWidget<UToonLayerWidget>(GetWorld(), LayerWidget))
	{
		// Set Layer properties. The ID is incremented here, ready for the next layer creation
		NewLayerWidget->InitLayer(LayerName, LayerIDCount++);

		// Create the underlying UMG UWidget. This is neccessary for the widget content to be added to viewport
		GetGameInstance()->GetGameViewportClient()->AddViewportWidgetContent(NewLayerWidget->TakeWidget());

		// Add the new layer to the subsytem layer list
		LayerList.Add(NewLayerWidget);

		// Return a reference to the blueprint
		return NewLayerWidget; 
	}
	
	UE_LOG(LogTemp, Error, TEXT("Failed to CreatLayerWidget. Create Widget cast failed"))

	return nullptr;
}

UToonActivatableWidget* UToonUISubsystem::PushWidgetByLayerName(const TSubclassOf<UToonActivatableWidget> Widget, const FString LayerName)
{
	if(UToonLayerWidget* Layer = GetLayerByName(LayerName))
	{
		if(UToonActivatableWidget* NewWidget = Layer->PushWidgetToLayer(Widget))
		{
			return NewWidget;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Layer could not be found. Failed to add widget"))
	
	return nullptr;
}


bool UToonUISubsystem::RemoveLayerByName(const FString LayerName)
{
	 if (const TObjectPtr<UToonLayerWidget> Layer = GetLayerByName(LayerName))
	 {
		Layer->ConditionalBeginDestroy();
	 	// LayerList.Remove(Layer);
	 
	 	return true;
	 }
	 
	 UE_LOG(LogTemp, Warning, TEXT("Failed to delete layer widget: Layer could not be found. "))
	 
	 return false;
}

bool UToonUISubsystem::RemoveLayerByID(const int ID)
{
	if (const TObjectPtr<UToonLayerWidget> Layer = GetLayerByID(ID))
	{
		Layer->ConditionalBeginDestroy();
		// LayerList.Remove(Layer);

		return true;
	}

	UE_LOG(LogTemp, Warning, TEXT("Failed to delete layer widget: Layer could not be found. "))

	return false;
}


TArray<FToonLayerData> UToonUISubsystem::GetAllLayerData()
{
	TArray<FToonLayerData> LayerDataStructs;

	for (const TObjectPtr<UToonLayerWidget> Layer : LayerList) { LayerDataStructs.Add(Layer->GetLayerData()); }

	return LayerDataStructs;
}


UToonLayerWidget* UToonUISubsystem::GetLayerByName(const FString LayerName)
{
	const FString LayerLowerCase = LayerName.ToLower();

	for (UToonLayerWidget* Layer : LayerList)
		if (Layer->GetLayerName().ToLower() == LayerLowerCase) return Layer;

	return nullptr;
}

TArray<FString> UToonUISubsystem::GetAllLayerNames()
{
	TArray<FString> LayerNames;

	for (const TObjectPtr<UToonLayerWidget> Layer : LayerList) { LayerNames.Add(Layer->GetLayerName()); }
	return LayerNames;
}


UToonLayerWidget* UToonUISubsystem::GetLayerByID(const int LayerID)
{
	for (UToonLayerWidget* Layer : LayerList)
		if (Layer->GetLayerID() == LayerID) return Layer;

	return nullptr;
}

TArray<int> UToonUISubsystem::GetAllLayerIDs()
{
	TArray<int> LayerIDs;

	for (const TObjectPtr<UToonLayerWidget> Layer : LayerList) { LayerIDs.Add(Layer->GetLayerID()); }

	return LayerIDs;
}


