// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonHealthComponent.h"
// Fill out your copyright notice in the Description page of Project Settings.


#include "Kismet/GameplayStatics.h"
#include "ToonTanks/GameModes/ToonGameMode.h"

UToonHealthComponent::UToonHealthComponent()
{
	
	PrimaryComponentTick.bCanEverTick = true;


	Health = MaxHealth;
}




// Called when the game starts
void UToonHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UToonHealthComponent::OnApplyDamage);
	ToonTankGameMode = Cast<AToonGameMode>(UGameplayStatics::GetGameMode(this));
}


// Called every frame
void UToonHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UToonHealthComponent::OnApplyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	AController* InstigatedBy, AActor* DamageCauser)
{
	// Check for no damage
	if (Damage <= 0.0f) return;

	// Apply damage
	Health -= Damage;

	// Check actor died
	if (Health <= 0.f)
	{
		ToonTankGameMode->ActorDied(DamagedActor);
	}
}