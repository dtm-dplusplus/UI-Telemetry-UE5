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
	
	// Creates a UI Layer which widgets can be added to
	UFUNCTION(BlueprintCallable)
	UToonLayerWidget* CreatLayerWidget(TSubclassOf<UToonLayerWidget> LayerWidget, FString LayerName);

	// Add a widget to the corresponding layer by name (case insensitve)
	UFUNCTION(BlueprintCallable)
	UToonActivatableWidget* PushWidgetByLayerName(TSubclassOf<UToonActivatableWidget> Widget, FString LayerName);

	// Returns a layer pointer if one with a macthing name can be found in the layer list
	UFUNCTION(BlueprintCallable)
	UToonLayerWidget* GetLayerByName(FString LayerName);

	// Returns a list of the active layer names
	UFUNCTION(BlueprintCallable)
	TArray<FString> GetLayerNames();

private:
	// List of UI layers.
	// Accessible in blueprint via a pointer reference to the layer or via the layer name in PushWidgetToLayerName().
	TArray<TObjectPtr<UToonLayerWidget>> Layers;
};