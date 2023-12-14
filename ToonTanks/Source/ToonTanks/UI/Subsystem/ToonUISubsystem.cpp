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

	Layers.Empty();
}


UToonLayerWidget* UToonUISubsystem::CreatLayerWidget(TSubclassOf<UToonLayerWidget> LayerWidget)
{
	// Create New Toon Layer Widget
	if(UToonLayerWidget* NewLayerWidget = CreateWidget<UToonLayerWidget>(GetWorld(), LayerWidget))
	{
		// Create the underlying UMG UWidget. This is neccessary for the widget content to be added to viewport
		GetGameInstance()->GetGameViewportClient()->AddViewportWidgetContent(NewLayerWidget->TakeWidget());

		// Add the new layer to the subsytem list. Each layer can be added to by
		Layers.Add(NewLayerWidget);

		return NewLayerWidget; 
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Failed to CreatLayerWidget"))

	return nullptr;
}
