// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonMenuPawn.h"

#include "Camera/CameraComponent.h"
// Sets default values
AToonMenuPawn::AToonMenuPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	RootComponent = Camera;
}
