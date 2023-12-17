// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonUISubsystem.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/GameViewportClient.h"
#include "ToonTanks/UI/ToonLayerWidget.h"

void UToonUISubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

}

void UToonUISubsystem::Deinitialize()
{
	Super::Deinitialize();

}

UToonLayerWidget* UToonUISubsystem::CreatLayerWidget(const TSubclassOf<UToonLayerWidget> LayerWidget, const FString LayerName)
{
	// Check a layer with name argument does not already exist. 
	if (GetLayerNames().Contains(LayerName))
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to CreatLayerWidget. A layer with this name already exists"))
		return nullptr;
	}

	// Create New Toon Layer Widget
	if(UToonLayerWidget* NewLayerWidget = CreateWidget<UToonLayerWidget>(GetWorld(), LayerWidget))
	{
		NewLayerWidget->SetLayerName(LayerName);

		// Create the underlying UMG UWidget. This is neccessary for the widget content to be added to viewport
		GetGameInstance()->GetGameViewportClient()->AddViewportWidgetContent(NewLayerWidget->TakeWidget());

		// Add the new layer to the subsytem layer list
		Layers.Add(NewLayerWidget);

		// Return a reference to the blueprint
		return NewLayerWidget; 
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Failed to CreatLayerWidget"))

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

UToonLayerWidget* UToonUISubsystem::GetLayerByName(const FString LayerName)
{
	const FString LayerLowerCase = LayerName.ToLower();

	for(UToonLayerWidget* Layer : Layers)
		if (Layer->GetLayerName().ToLower() == LayerLowerCase) return Layer;

	return nullptr;
}

TArray<FString> UToonUISubsystem::GetLayerNames()
{
	TArray<FString> LayerNames;

	for (const TObjectPtr<UToonLayerWidget> Layer : Layers) { LayerNames.Add(Layer->GetLayerName()); }
	return LayerNames;
}