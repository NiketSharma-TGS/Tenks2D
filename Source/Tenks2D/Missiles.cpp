// Fill out your copyright notice in the Description page of Project Settings.


#include "Missiles.h"

// Sets default values
AMissiles::AMissiles()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMissiles::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMissiles::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

