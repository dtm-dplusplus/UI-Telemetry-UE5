// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonLayerWidget.h"

void UToonLayerWidget::InitLayer(FString Name, const int ID)
{
	LayerData.LayerName = Name;
	LayerData.LayerID = ID;
}



UToonActivatableWidget* UToonLayerWidget::PushWidgetToLayer(TSubclassOf<UToonActivatableWidget> Widget)
{
	// Add a new widget to the layer by pushing it onto the underlying CommonActivatableStack.
	// No need to manually activate the widget, the top most widget on the stack becomes activated by default. 
	if(LayerStack)
	{
		if(UToonActivatableWidget* NewWidget = Cast<UToonActivatableWidget>(LayerStack->AddWidget(Widget)))
			return NewWidget;
	}

	UE_LOG(LogTemp, Warning, TEXT("LayerStack or widget is invalid"));
	return nullptr;
}

void UToonLayerWidget::DeactivateWidgetFromLayer()
{
	LayerStack->GetActiveWidget()->DeactivateWidget();
}