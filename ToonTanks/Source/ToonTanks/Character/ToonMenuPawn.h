// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ToonMenuPawn.generated.h"

UCLASS()
class TOONTANKS_API AToonMenuPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AToonMenuPawn();

	// Camera Properties //
	UPROPERTY(EditAnywhere, Category = "Camera")
	TObjectPtr<class UCameraComponent> Camera;
};
