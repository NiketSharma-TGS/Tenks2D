// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Components/ArrowComponent.h"
#include "PaperSpriteComponent.h"
#include "Turret.h"

// Sets default values
ATurret::ATurret()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("TurretBase"));

	TurretDirection = CreateDefaultSubobject<UArrowComponent>(TEXT("TurretDirection"));
	TurretDirection->AttachTo(RootComponent);
	
}

// Called when the game starts or when spawned
void ATurret::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

