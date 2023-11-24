#include "ToonPawn.h"

AToonPawn::AToonPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	SetCanBeDamaged(false);
}
