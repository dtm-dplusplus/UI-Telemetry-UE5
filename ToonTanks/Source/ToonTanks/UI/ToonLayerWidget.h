// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ToonActivatableWidget.h"
#include "ToonActivatableWidgetStack.h"
#include "ToonLayerWidget.generated.h"

class UToonActivatableWidgetStack;


// The Layer Widget allows widgets to be pushed onto a widget stack. Only the top most widget will be activated.
// When a widget is popped/removed from the top of the stack, the widget beneath it becomes the active widget of the layer.
UCLASS()
class TOONTANKS_API UToonLayerWidget : public UToonActivatableWidget
{
	GENERATED_BODY() 

public:

	// Adds a widget to the layer and activates it. 
	UFUNCTION(BlueprintCallable)
	UToonActivatableWidget* PushWidgetToLayer(TSubclassOf<UToonActivatableWidget> Widget);

	// Set the layer name for UI Subsytem functionallity. 
	void SetLayerName(FString Name) { LayerName = Name; }

	// Get the layer name for UI Subsytem functionallity. 
	FString GetLayerName() { return LayerName; }

protected:

	// The name of the layer. Set by the layer name argument passed to the Subsystem CreateLayer function.
	// The name is unique to this subsystem and has no effect on UMG or CommonUI functionallity.
	UPROPERTY(BlueprintReadWrite)
	FString LayerName;

	// The widget stack onto which widgets are added
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UToonActivatableWidgetStack> LayerStack;
};
