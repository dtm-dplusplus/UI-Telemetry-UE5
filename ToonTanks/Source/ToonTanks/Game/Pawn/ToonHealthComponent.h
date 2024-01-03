// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ToonHealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams(FOnHealthChangedDelegate, UToonHealthComponent*, HealthComponent, float, Health, float, DamageAmount, const class UDamageType*, DamageType, class AController*, InstigatedBy, AActor*, DamageCauser);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOONTANKS_API UToonHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UToonHealthComponent();

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnHealthChangedDelegate OnHealthChanged;

	// Health Properties //
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Health Component", meta = (AllowPrivateAccess = "true"))
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Health Component", meta = (AllowPrivateAccess = "true"))
	float MaxHealth;
	

	UFUNCTION(BlueprintCallable)
	void HandleTakeDamage(AActor* DamageActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

protected:
	virtual void BeginPlay() override;

private:
	TWeakObjectPtr<class AToonGameMode> ToonGameMode;
};
