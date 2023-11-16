// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOONTANKS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHealthComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;

private:
	// Health Properties //
	// Default Health value
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Health Component", meta = (AllowPrivateAccess = "true"))
	float MaxHealth = 100.f;

	// Current Health
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Health Component", meta = (AllowPrivateAccess = "true"))
	float Health = 0.f;

	// Applies damage to health when projectile hits actor
	UFUNCTION()
	void OnTakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	// Reference to the GameMode
	TObjectPtr<class AToonTankGameMode> ToonTankGameMode;
};
