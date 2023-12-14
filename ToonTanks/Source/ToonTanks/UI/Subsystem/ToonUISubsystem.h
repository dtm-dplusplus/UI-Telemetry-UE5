// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ToonUISubsystem.generated.h"

class UToonActivatableWidget;
class UToonLayerWidget;

UCLASS()
class TOONTANKS_API UToonUISubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	// Add a widget to the layer with the corresponding layer name
	// The Layer Name is case insensitve
	// UFUNCTION(BlueprintCallable) 
	// void PushWidgetToLayerName(TSubclassOf<UToonActivatableWidget> LayerWidget, FString LayerName);

	// Creates a UI Layer which widget can be added to.
	// Widgets can be added to the layer anywhere 
	UFUNCTION(BlueprintCallable)
	UToonLayerWidget* CreatLayerWidget(TSubclassOf<UToonLayerWidget> LayerWidget);

	// List of UI layers.
	// Accessible in blueprint via a pointer reference to the layer or via the layer name in PushWidgetToLayerName().
	TArray<TObjectPtr<UToonLayerWidget>> Layers;
};