// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TimerManager.h"
#include "Missile.h"


// Sets default values
AMissile::AMissile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Speed = 200.0f;
}

// Called when the game starts or when spawned
void AMissile::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle DummyTimerHandle;
	GetWorldTimerManager().SetTimer(DummyTimerHandle, this, &AMissile::Explode, 1.0f);
}

// Called every frame
void AMissile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector Loc = GetActorLocation();
	Loc += (DeltaTime * Speed) * GetTransform().GetUnitAxis(EAxis::X);
	SetActorLocation(Loc);
}

void AMissile::Explode_Implementation()
{
	Destroy();
}

