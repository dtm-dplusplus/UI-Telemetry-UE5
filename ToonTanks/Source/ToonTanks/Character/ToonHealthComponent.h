// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ToonHealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOONTANKS_API UToonHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UToonHealthComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void OnApplyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
protected:
	virtual void BeginPlay() override;

private:
	// Health Properties //
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Health Component", meta = (AllowPrivateAccess = "true"))
	float MaxHealth = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Health Component", meta = (AllowPrivateAccess = "true"))
	float Health = MaxHealth;

	TObjectPtr<class AToonGameMode> ToonTankGameMode;
};
