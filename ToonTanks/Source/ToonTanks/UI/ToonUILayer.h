// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "ToonUILayer.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API UToonUILayer : public UCommonUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

};
