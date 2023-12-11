// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUI/Public/CommonActivatableWidget.h"
#include "ToonUILayer.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API UToonUILayer : public UCommonActivatableWidget
{
	GENERATED_BODY()

public:
	UToonUILayer();

	void SetLayerName(FString Name) { LayerName = Name; }

	FString GetLayerName() { return LayerName; }

protected:
	UPROPERTY(EditDefaultsOnly)
	FString LayerName;
};
