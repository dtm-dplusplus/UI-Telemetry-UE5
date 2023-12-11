// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonUISubsystem.h"
#include "CommonActivatableWidget.h"
#include "Widgets/CommonActivatableWidgetContainer.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/GameViewportClient.h"

void UToonUISubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	UE_LOG(LogTemp, Warning, TEXT("Initialised UI Subsytem"))


}

void UToonUISubsystem::PushWidget(TSubclassOf<UCommonActivatableWidget> Widget)
{
	if(Widget)
	{
		// if (WidgetStacks[StackIndex])
		// {
		// 	WidgetStacks[StackIndex]->AddWidget(Widget);
		// 
		// 	UE_LOG(LogTemp, Warning, TEXT("Pushed Widget to Stack"))
		// }
		// else
		// {
		// 	UE_LOG(LogTemp, Warning, TEXT("Failed to Push Widget to Stack"))
		// 
		// }


	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid Widget reference"))

	}
}

UCommonActivatableWidget* UToonUISubsystem::CreatLayerWidget(TSubclassOf<UCommonActivatableWidget> LayerWidget, FString LayerName)
	
{
	if(UCommonActivatableWidget* SlateWidget = CreateWidget<UCommonActivatableWidget>(GetWorld(), LayerWidget))
	{
		GetGameInstance()->GetGameViewportClient()->AddViewportWidgetContent(SlateWidget->TakeWidget());
		UE_LOG(LogTemp, Warning, TEXT("Successfully CreatLayerWidget"))

			return SlateWidget;
	}

	UE_LOG(LogTemp, Warning, TEXT("Failed to CreatLayerWidget"))
		return nullptr;
}
