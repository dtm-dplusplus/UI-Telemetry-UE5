// Fill out your copyright notice in the Description page of Project Settings.

#include "ToonLayerWidget.h"

UToonActivatableWidget* UToonLayerWidget::PushWidgetToLayer(const TSubclassOf<UToonActivatableWidget> Widget)
{
	if(LayerStack)
	{
		if(UToonActivatableWidget* NewWidget = Cast<UToonActivatableWidget>(LayerStack->AddWidget(Widget)))
			return NewWidget;
	}

	UE_LOG(LogTemp, Warning, TEXT("PushWidgetToLayer: LayerStack or widget is invalid"));
	return nullptr;
}