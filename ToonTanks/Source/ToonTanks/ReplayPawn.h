// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpectatorPawn.h"
#include "ReplayPawn.generated.h"

class UInputAction;

UCLASS()
class TOONTANKS_API AReplayPawn : public ASpectatorPawn
{
	GENERATED_BODY()

public:
	AReplayPawn();

	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	// UFUNCTION(BlueprintCallable, Category = "Replay")
	// void ToggleReplay();

	UFUNCTION(BlueprintCallable, Category = "Replay")
	void RestartReplay();

	// INPUT MAPPINGS //
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Replay|Enhanced Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputMappingContext> InputMappingContext;

	// UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Replay|Enhanced Input", meta = (AllowPrivateAccess = "true"))
	// TObjectPtr<UInputAction> InputToggleReplay;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Replay|Enhanced Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> InputRestartReplay;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Replay|Enhanced Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class AReplayPlayerController> ReplayPlayerController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Replay|Replay", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UReplayGameInstance> ReplayGameInstance;
};