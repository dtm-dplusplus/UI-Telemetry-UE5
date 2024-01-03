// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonHealthComponent.h"

#include "../../../../../../../../../../../Program Files/Epic Games/UE_5.2/Engine/Source/Runtime/Engine/Classes/Engine/World.h"
#include "Kismet/GameplayStatics.h"

#include "../GameMode/ToonGameMode.h"

UToonHealthComponent::UToonHealthComponent()
{
	MaxHealth = 100.f;
	Health = MaxHealth;
}

// Called when the game starts
void UToonHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	if (AActor* MyOwner = GetOwner())
	{
		//The Owner Object is now bound to respond to the OnTakeAnyDamage Function.        
		MyOwner->OnTakeAnyDamage.AddDynamic(this, &UToonHealthComponent::HandleTakeDamage);
	}

	ToonGameMode = Cast<AToonGameMode>(UGameplayStatics::GetGameMode(this));

	Health = MaxHealth;
}

void UToonHealthComponent::HandleTakeDamage(AActor* DamageActor, float Damage, const UDamageType* DamageType,
	AController* InstigatedBy, AActor* DamageCauser)
{
	// UE_LOG(LogTemp, Warning, TEXT("HandleTakeDamage on %s"), *GetOwner()->GetName())
	// Check for no damage
	if (Damage <= 0.0f)
	{
		return;
	}

	// Apply damage
	Health = FMath::Clamp(Health - Damage, 0.0f, MaxHealth);

	// Broadcast event to C++ & Blueprint
	OnHealthChanged.Broadcast(this, Health, Damage, DamageType, InstigatedBy, DamageCauser);

	// Notify gamemode actor should be dead. Destruction is handled there
	if (Health <= 0.0f)
	{
		ToonGameMode->ActorDied(DamageActor);
	}
}