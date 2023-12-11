// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonUILayer.h"

#include "Blueprint/WidgetTree.h"
#include "Components/Overlay.h"


void UToonUILayer::NativeConstruct()
{
	Super::NativeConstruct();

	// Create base layer overlay
	//LayerOverlay = WidgetTree->ConstructWidget<UOverlay>(UOverlay::StaticClass(), TEXT("Layer Overlay"));
	auto overlay = WidgetTree->ConstructWidget<UOverlay>();
	// Create ui layer stack
}
