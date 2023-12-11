// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonUISubsystem.h"
#include "CommonActivatableWidget.h"
#include "Widgets/CommonActivatableWidgetContainer.h"
#include "Engine/GameViewportClient.h"

void UToonUISubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	UE_LOG(LogTemp, Warning, TEXT("Initialised UI Subsytem"))


}

void UToonUISubsystem::PushStack(UCommonActivatableWidgetStack* WidgetStack)
{
	if(WidgetStack->IsConstructed())
	{
		//WidgetStacks.Add(WidgetStack);
		UE_LOG(LogTemp, Warning, TEXT("Pushed Stack to WidgetStacks"))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to Push Stack to WidgetStacks"))
	}
}

void UToonUISubsystem::PushWidget(TSubclassOf<UCommonActivatableWidget> Widget, uint8 StackIndex)
{
	if(Widget)
	{
		if (WidgetStacks[StackIndex])
		{
			WidgetStacks[StackIndex]->AddWidget(Widget);

			UE_LOG(LogTemp, Warning, TEXT("Pushed Widget to Stack"))
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to Push Widget to Stack"))

		}


	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid Widget reference"))

	}
	
}

void UToonUISubsystem::CreatLayerWidget(TSubclassOf<UCommonActivatableWidget> Widget)
{
	//if(auto Controller = GetGameInstance()->GetFirstLocalPlayerController())
	//{
	//	GetGameInstance()->GetGameViewportClient()->AddViewportWidgetContent(CreateWidget(Widget)->TakeWidget());
	//	PushWidget(Widget);
	//}
}