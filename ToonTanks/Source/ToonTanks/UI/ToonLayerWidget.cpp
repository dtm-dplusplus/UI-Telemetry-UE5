// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonLayerWidget.h"

// Adds and activates a new widget onto the layer
UToonActivatableWidget* UToonLayerWidget::PushWidgetToLayer(TSubclassOf<UToonActivatableWidget> Widget)
{
	// Add a new widget to the layer by pushing it onto the underlying CommonActivatableStack.
	// No need to manually activate the widget, the top most widget on the stack becomes activated by default. 
	if(LayerStack)
	{
		LayerStack->AddWidget(Widget);
		return Cast<UToonActivatableWidget>(LayerStack->GetActiveWidget());
	}

	UE_LOG(LogTemp, Warning, TEXT("Layer Widget LayerStack is invalid"));
	return nullptr;
}
