// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ToonUISubsystem.generated.h"

class UCommonActivatableWidgetStack;
class UCommonActivatableWidget;


UCLASS()
class TOONTANKS_API UToonUISubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UFUNCTION(BlueprintCallable)
	void PushStack(UCommonActivatableWidgetStack* WidgetStack);

	UFUNCTION(BlueprintCallable)
	void PushWidget(TSubclassOf<UCommonActivatableWidget> Widget, uint8 StackIndex);

	UFUNCTION(BlueprintCallable)
	void CreatLayerWidget(TSubclassOf<UCommonActivatableWidget> Widget);


	TArray<UCommonActivatableWidgetStack*> WidgetStacks;
};